// 是否在数组内
function in_array(needle, haystack) {
    if(typeof needle == 'string' || typeof needle == 'number') {
        for(var i in haystack) {
            if(haystack[i] == needle) {
                return true;
            }
        }
    }
    return false;
}

function setSearchValue(inputObject, objectValue){
    var maxInputLength = (inputObject.width() - 30)/13;
    if(objectValue.length>maxInputLength){
        inputObject.val(objectValue.substring(0,maxInputLength)+'...');
        inputObject.attr("title",objectValue);
    }else{
        inputObject.val(objectValue);
    }
}