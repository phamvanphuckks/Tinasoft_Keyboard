const constKey = {
	/////////////hang 1
	r1c1: [
		'008\r\n'
	], //e
	r1c2: [
		'026\r\n'
	], //w
	r1c3: [
		'029\r\n'
	], //z
	r1c4: [
		'260\r\n'
	], //Z
	r1c5: [
		'261\r\n'
	], //Q
	r1c6: [
		'087\r\n'
	], //+
	r1c7: [
		'258\r\n'
	], //W
	r1c8: [
		'004\r\n'
	], //a
	r1c9: [
		'057\r\n',
		'045\r\n',
		'057\r\n'
	], //-
	r1c10: [
		'262\r\n'
	], //>  
	r1c11: [
		'225\r\n'
	], //?
	r1c12: [
		'051\r\n'
	], //;
	/////////////hang2
	LOCK: [], //c1
	HELP: [
		'011\r\n'
	], //h
	'Bao 5': [
		'263\r\n'
	], //G
	'Mega 6/45': [
		'015\r\n'
	], //l
	Keno: [
		'007\r\n'
	], //d
	'MAX 4D': [
		'028\r\n'
	], //y
	'Tổ hợp': [
		'024\r\n'
	], //u
	'Vé bao': [
		'016\r\n'
	], //m
	A: [
		'237\r\n'
	], //A
	DOWN: [
		'047\r\n'
	], //[
	UP: [
		'048\r\n'
	], //]
	CLEAR: [
		'103\r\n'
	], //=
	/////////////hang 3
	EXIT: [
		'238\r\n'
	], //S
	REPORT: [
		'005\r\n'
	], //b
	'Bao 7': [
		'239\r\n'
	], //H
	'POWER 6/55': [
		'014\r\n'
	], //k
	r3c5: [
		'009\r\n'
	], //c5
	'MAX 3D': [
		'240\r\n'
	], //N
	'Cuộn 1': [
		'241\r\n'
	], //M
	'Cuộn 4': [
		'226\r\n'
	], //<
	B: [
		'256\r\n'
	], //B
	'1': [
		'030\r\n'
	], //1
	'2': [
		'031\r\n'
	], //2
	'3': [
		'032\r\n'
	], //3
	/////////////hang4
	FUNC: [
		'022\r\n'
	], //s
	PRINT: [
		'021\r\n'
	], //r
	'Bao 8': [
		'242\r\n'
	], //J
	r4c4: [
		'013\r\n'
	], //j
	r4c5: [
		'010\r\n'
	], //g
	'Max 3D+': [
		'020\r\n'
	], //q
	'10K': [
		'227\r\n'
	], //!
	'200K': [
		'228\r\n'
	], //%
	C: [
		'243\r\n'
	], //C
	'4': [
		'033\r\n'
	], //4
	'5': [
		'034\r\n'
	], //5
	'6': [
		'035\r\n'
	], //6

	/////////////hang5
	r5c1: [
		'244\r\n'
	], //R
	r5c2: [
		'019\r\n'
	], //p
	'Bao 9': [
		'245\r\n'
	], //K
	r5c4: [
		'246\r\n'
	], //T
	'TỰ CHỌN': [
		'259\r\n'
	], //I
	r5c6: [
		'012\r\n'
	], //i
	'20K': [
		'229\r\n'
	], //@
	'500K': [
		'230\r\n'
	], //^
	D: [
		'247\r\n'
	], //D
	'7': [
		'036\r\n'
	], //7
	'8': [
		'037\r\n'
	], //8
	'9': [
		'038\r\n'
	], //9

	/////////////hang6
	RECALL: [
		'006\r\n'
	], //c
	SALE: [
		'017\r\n'
	], //n
	'BAO#': [
		'248\r\n'
	], //L
	'1KY': [
		'249\r\n'
	], //Y
	'2KY': [
		'250\r\n'
	], //O
	'3KY': [
		'018\r\n'
	], //o
	'50K': [
		'231\r\n'
	], //#
	'1000K': [
		'232\r\n'
	], //&
	'E': [
		'251\r\n'
	], //O
	BACKSPACE: [
		'042\r\n'
	], //BACK SPACE
	'0': [
		'039\r\n'
	], //0
	DOS: [
		'055\r\n'
	], //.

	/////////////hang7
	CANCEL: [
		'025\r\n'
	], //v
	PAY: [
		'252\r\n'
	], //V
	r7c3: [
		'233\r\n'
	], //:
	'4KY': [
		'253\r\n'
	], //U
	'5KY': [
		'254\r\n'
	], //P
	'6KY': [
		'234\r\n'
	], //{
	'100K': [
		'235\r\n'
	], //$
	'GIA#': [
		'085\r\n'
	], //*
	'F': [
		'255\r\n'
	], //F
	'SEND': [
		'027\r\n'
	], //x
	'TOTAL': [
		'023\r\n'
	], //t
};

const customkey = {
	// custom
	'Bao 10': constKey["A"],
	'Bao 11': constKey["B"],
	'Bao 12': constKey["C"],
	'Bao 13': constKey["D"],
	'Bao 14': constKey["E"],
	'Bao 15': constKey["F"],
	'Bao 18': constKey["1"],

	'30K': constKey["10K"].concat(constKey["20K"]),

	'10KY': constKey["1KY"].concat(constKey["A"]),
	'20KY': constKey["1KY"].concat(constKey["B"]),
	'30KY': constKey["1KY"].concat(constKey["C"]),

	'empty': null
}

module.exports = {
	constKey: Object.assign({}, constKey,customkey)
};