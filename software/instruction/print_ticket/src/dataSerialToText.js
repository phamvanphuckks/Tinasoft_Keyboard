const constKey = require('../config/key').constKey;
let output = "";

function findJson(obj, field, value ) {
    for (var name in obj) {
      if(obj[name][field] == value){
        return name+",";
      }
    }
    return "undefined,"
}

const a=[
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
]

for (let i = 0; i < a.length; i++) {
    output+= findJson(constKey,0,a[i]);
}
console.log(output);
