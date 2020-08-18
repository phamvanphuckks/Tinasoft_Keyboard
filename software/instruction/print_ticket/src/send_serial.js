const delay = (time) => new Promise((res) => setTimeout(res, time));
const isNumberKey = [
	'030\r\n',
	'031\r\n',
	'032\r\n',
	'033\r\n',
	'034\r\n',
	'035\r\n',
	'036\r\n',
	'037\r\n',
	'038\r\n',
	'039\r\n',
	null,
]

async function sendSerial(port, data, productOptionId) {
	var lengData = data.length;
	for (let indexCharSend = 0; indexCharSend < lengData; indexCharSend++) {
		try {
			if ( isNumberKey.includes(data[indexCharSend]) ) {
				productOptionId === 82 ? await delay(150) : await delay(300);
			} else{
				await delay(500);
				
			}
			if( data[indexCharSend]!== null) port.write(data[indexCharSend]);
			else if( data[indexCharSend] === undefined ) return false;
			if(indexCharSend >= lengData) return false
		} catch (error) {
			console.log('Khong the gui, kiem tra ket noi');
			return false
		}
	}
	return false;
}

module.exports = {
	sendSerial : sendSerial
};
