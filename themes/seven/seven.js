function setSearchValue(inputObject, objectValue) {
    var maxInputLength = (inputObject.width() - 30) / 13;
    if (objectValue.length > maxInputLength) {
        inputObject.val(objectValue.substring(0, maxInputLength) + '...');
        inputObject.attr("title", objectValue);
    } else {
        inputObject.val(objectValue);
    }
}