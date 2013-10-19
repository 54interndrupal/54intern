// 是否在数组内
function in_array(needle, haystack) {
    if (typeof needle == 'string' || typeof needle == 'number') {
        for (var i in haystack) {
            if (haystack[i] == needle) {
                return true;
            }
        }
    }
    return false;
}

function setSearchValue(inputObject, objectValue) {
    var maxInputLength = (inputObject.width()) / 14;
    if (objectValue.length > maxInputLength) {
        inputObject.val(objectValue.substring(0, maxInputLength) + '...');
        inputObject.attr("title", objectValue);
    } else {
        inputObject.val(objectValue);
    }
}

function showMessage(message) {
    //alert('xx'+message+'yy');
    if (message && message!= '') {
        jQuery('#messages').empty();
        jQuery("#main").prepend('<div id="messages"><div class="section clearfix"><div class="messages status"><h2 class="element-invisible">状态消息</h2>' +
            message + '</div></div></div>');
    }
}
