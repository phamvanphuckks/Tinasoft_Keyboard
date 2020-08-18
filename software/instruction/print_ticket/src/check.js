function checkConsecutiveTerm(termArr,currentTerm) {
    if(termArr[0]!=currentTerm) return false
    else{
        for (let index = 1; index < termArr.length; index++) {
            if(termArr[i]!== termArr[i-1]+1) return false
        }
        return true;
    }
}

module.exports={
    checkConsecutiveTerm: checkConsecutiveTerm
}