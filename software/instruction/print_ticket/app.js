// INIT
var config = require('./config/appConfig.json');
var app = require('express')();
var http = require('http').Server(app).listen(config.postSocket);
var io = require('socket.io')(http);
const fs = require("fs");
const moment = require("moment") ;
const log = require("log-to-file");

// require config
var product = require('./config/product.json');
var productOption = require('./config/productOption.json');
var keyABCD = require('./config/keyABCD.json');
var constKey = require('./config/key.js').constKey;

// require file to content
const sendSerial = require('./src/send_serial').sendSerial;
const check = require('./src/check');


// lib serial
const SerialPort = require('serialport');
const serialportgsm = require('serialport-gsm');
var port = null;
var wait = false;
// list com port && select port
serialportgsm.list((err, result) => {
	if (err) {
		console.log('LOI TIM SERIAL PORT');
	}
	else {
		switch (result.length) {
			case 0:
				console.log('KHONG CO THIET BI KET NOI');
				break;
			case 1:
				port = new SerialPort(result[0].comName, {
					baudRate : config.baudRate
				});
				console.log('KET NOI MAY BAN VE THANH CONG ' + result[0].comName);
				break;
			default:
				for (let index = 0; index < result.length; index++) {
					const element = result[index];
					if(element.manufacturer == 'Silicon Labs'){
						console.log('CO NHIEU HON 1 THIET BI KET NOI. CHON ' + element.comName);
						port = new SerialPort(element.comName, {
							baudRate : config.baudRate
						});
					}
				}
				break;
		}
	}
});

async function handDataRecever(data) {
	wait = true;
	var _product = product[data.productId];
	var _productOption = productOption[data.productOptionId];
	var dataSend = [];
	console.log(_product, _productOption, data.id,  moment().format('HH:mm:ss DD-MM-YYYY '));
	log("-------------------------------");
	log(_product +"_"+ _productOption +"_"+ data.id +"_"+ moment().format('HH:mm:ss DD-MM-YYYY '));
	log(JSON.stringify(data));
	switch (data.productId) {
		case 1:  //Mega 6/45
			data.termArray.forEach((termTicket) => {
				dataSend = dataSend.concat(constKey.A); // vao mode tro choi
				dataSend = dataSend.concat(constKey[_product]); // chon loai ve
				if (_productOption != 'Vé đơn') {
					if(data.productOptionId<=5){
						dataSend = dataSend.concat(constKey[_productOption]); // chon kieu choi
					}
					else{
						dataSend = dataSend.concat(constKey["BAO#"]); // chon kieu choi
						dataSend = dataSend.concat(constKey["BAO#"]); // chon kieu choi
						dataSend = dataSend.concat(constKey[_productOption]); // chon kieu choi
					}
				}
				dataSend = dataSend.concat(constKey[keyABCD[termTicket - data.currentTerm.termValue + 1]]); // chon ky
				dataSend = dataSend.concat(constKey[keyABCD[termTicket - data.currentTerm.termValue + 1]]); // chon ky
				//chon so
				data.value.forEach((arrayNumber) => {
					// chon so
					arrayNumber.number.forEach((number) => {
						for (let index = 0; index < number.length; index++) {
							dataSend = dataSend.concat(constKey[number[index]]);
						}
					});
				});
				dataSend = dataSend.concat(constKey.SEND);
			});
			break;
		case 2: // POWER 6/55
			data.termArray.forEach((termTicket) => {
				dataSend = dataSend.concat(constKey.A); // vao mode tro choi
				dataSend = dataSend.concat(constKey[_product]); // chon loai ve
				if (_productOption != 'Vé đơn') {
					if(data.productOptionId<=25){
						dataSend = dataSend.concat(constKey[_productOption]); // chon kieu choi
						// dataSend = dataSend.concat(constKey[_productOption]); // chon kieu choi
					}
					else{
						dataSend = dataSend.concat(constKey["BAO#"]); // chon kieu choi
						dataSend = dataSend.concat(constKey["BAO#"]); // chon kieu choi
						dataSend = dataSend.concat(constKey[_productOption]); // chon kieu choi
					}
				}
				dataSend = dataSend.concat(constKey[keyABCD[termTicket - data.currentTerm.termValue + 1]]); // chon ky
				dataSend = dataSend.concat(constKey[keyABCD[termTicket - data.currentTerm.termValue + 1]]); // chon ky
				//chon so
				data.value.forEach((arrayNumber) => {
					// chon so
					arrayNumber.number.forEach((number) => {
						for (let index = 0; index < number.length; index++) {
							dataSend = dataSend.concat(constKey[number[index]]);
						}
					});
				});
				dataSend = dataSend.concat(constKey.SEND);
			});
			break;
		case 3: // MAX 4D
			data.termArray.forEach((termTicket) => {
				dataSend = dataSend.concat(constKey.A); // vao mode tro choi
				dataSend = dataSend.concat(constKey[_product]); // chon loai ve
				if (_productOption != 'Vé đơn') {
					dataSend = dataSend.concat(constKey[_productOption]); // chon kieu choi
					dataSend = dataSend.concat(constKey[_productOption]); // chon kieu choi
				}
				dataSend = dataSend.concat(constKey[keyABCD[termTicket - data.currentTerm.termValue + 1]]); // chon ky
				dataSend = dataSend.concat(constKey[keyABCD[termTicket - data.currentTerm.termValue + 1]]); // chon ky
				// chon so
				data.value.forEach((arrayNumber) => {
					// chon so
					arrayNumber.number.forEach((number) => {
						for (let index = 0; index < number.length; index++) {
							dataSend = dataSend.concat(constKey[number[index]]);
						}
					});
					//chon gia
					dataSend = dataSend.concat(constKey[arrayNumber.price + 'K']);
					dataSend = dataSend.concat(constKey.DOWN);
				});
				dataSend = dataSend.concat(constKey.SEND);
			});
			break;
		case 4: // MAX 3D
			data.termArray.forEach((termTicket) => {
				dataSend = dataSend.concat(constKey.A); // vao mode tro choi
				dataSend = dataSend.concat(constKey[_product]); // chon loai ve
				dataSend = dataSend.concat(constKey[keyABCD[termTicket - data.currentTerm.termValue + 1]]); // chon ky
				dataSend = dataSend.concat(constKey[keyABCD[termTicket - data.currentTerm.termValue + 1]]); // chon ky
				// chon so
				data.value.forEach((arrayNumber) => {
					// chon so
					arrayNumber.number.forEach((number) => {
						for (let index = 0; index < number.length; index++) {
							dataSend = dataSend.concat(constKey[number[index]]);
						}
					});
					//chon gia
					dataSend = dataSend.concat(constKey[arrayNumber.price + 'K']);
					dataSend = dataSend.concat(constKey.DOWN);
				});
				dataSend = dataSend.concat(constKey.SEND);
			});
			break;
		case 5: //"MAX 3D+"
			data.termArray.forEach((termTicket) => {
				dataSend = dataSend.concat(constKey.A); // vao mode tro choi
				dataSend = dataSend.concat(constKey["Max 3D+"]); // chon loai ve
				dataSend = dataSend.concat(constKey[keyABCD[termTicket - data.currentTerm.termValue + 1]]); // chon ky
				dataSend = dataSend.concat(constKey[keyABCD[termTicket - data.currentTerm.termValue + 1]]); // chon ky
				// chon so
				data.value.forEach((arrayNumber) => {
					// chon so
					arrayNumber.number.forEach((number) => {
						for (let index = 0; index < number.length; index++) {
							dataSend = dataSend.concat(constKey[number[index]]);
						}
					});
					// chon gia
					dataSend = dataSend.concat(constKey[arrayNumber.price + 'K']);
					dataSend = dataSend.concat(constKey.DOWN);
				});
				dataSend = dataSend.concat(constKey.SEND);
			});
			break;
			case 6: // Keno
			var termTicket = data.termArray.length.toString();
			if(data.termArray[0] === data.currentTerm.termValue){
				console.log("inve");
				dataSend = dataSend.concat(constKey.A); // vao mode tro choi
				dataSend = dataSend.concat(constKey[_product]); // chon loai ve
				//chia 2 TH keno so va tai xiu chan le
				if (data.productOptionId === 82) {
					// keno chan le tai xiu
					if(["1","2","3","5","10","20","30"].includes(termTicket)){
						dataSend = dataSend.concat(constKey[termTicket + 'KY']); // chon ky co san
						dataSend = dataSend.concat(constKey[termTicket + 'KY']); // chon ky co san
					}else{
						dataSend = dataSend.concat(constKey.D);
						dataSend = dataSend.concat(constKey.D);
						for (let index = 0; index < termTicket.length; index++) {
							dataSend = dataSend.concat( constKey[termTicket[index]]);
						}
						dataSend = dataSend.concat(constKey.SEND);
					}
					// chon so
					data.value.forEach((arrayNumber) => {
						//chon gia
						dataSend = dataSend.concat(constKey[arrayNumber.price + 'K']);
						// chon so
						arrayNumber.number.forEach((number) => {
							dataSend = dataSend.concat(constKey.F); // chọn vào nút bổ sung
							dataSend = dataSend.concat(constKey.empty); // tang delay
							dataSend = dataSend.concat(constKey[(5 - parseInt(number[0], 10)).toString()]); // chon key 1234 tuong ung tài xiu chan le
							dataSend = dataSend.concat(constKey.empty); // tang delay
						});
						dataSend = dataSend.concat(constKey.DOWN);
					});
					dataSend = dataSend.concat(constKey.SEND);
				}
				else {
					// keno so
					if(["1","2","3","5","10","20","30"].includes(termTicket)){
						dataSend = dataSend.concat(constKey[termTicket + 'KY']); // chon ky co san	
						dataSend = dataSend.concat(constKey[termTicket + 'KY']); // chon ky co san	
					} else{
						dataSend = dataSend.concat(constKey.D);
						dataSend = dataSend.concat(constKey.D);
						for (let index = 0; index < termTicket.length; index++) {
							console.log(termTicket[index]);
							dataSend = dataSend.concat( constKey[termTicket[index]]);
						}
						dataSend = dataSend.concat(constKey.SEND);
					}
					
					// chon so
					data.value.forEach((arrayNumber) => {
						// chon so
						arrayNumber.number.forEach((number) => {
							for (let index = 0; index < number.length; index++) {
								dataSend = dataSend.concat(constKey[number[index]]);
							}
						});
						// 	//chon gia
						dataSend = dataSend.concat(constKey[arrayNumber.price + 'K']);
						dataSend = dataSend.concat(constKey.DOWN);
					});
					dataSend = dataSend.concat(constKey.SEND);
				}
			}
			break;
		default:
			break;
	}
	wait = await sendSerial(port, dataSend);
	log(JSON.stringify(dataSend));
}

// check log file
try {
	var sizeLogFile = fs.statSync("default.log").size/1024;
	if(sizeLogFile > 10000){
		fs.writeFile("default.log","",function(){console.log("xoa log file")});
	}
} catch (error) {}

// socket
io.on('connection', function(socket) {
	socket.on(config.topic, async function(dataRecever) {
		if(!wait){
			wait = true;
			await handDataRecever(dataRecever);
		}else{
			console.log("Khong thu hien in ve. Chua in ve xong");
		}
	});
});


module.exports = app;
