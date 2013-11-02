var ind_flag_arr = new Array();		//	已选中数组
var ind_element_id;
//var ind_flag_arr = new Array('21','31','37');

var Industry = {
    // 行业列表
    init : function(){
        var _str='',_id='';
        if (ind_flag_arr.length>0){
            for (var i in ind_flag_arr){
                _str+=','+ind_a[ind_flag_arr[i]];
                _id+=','+ind_flag_arr[i];
            }
            jQuery('#btn_IndustryID').val(_str.substring(1));
            jQuery('#IndustryID').val(_id.substring(1));
        }
    },
    Show : function(){
        var output='',flag,output2='';
        for (var i in ind_a){
            flag=in_array(i,ind_flag_arr)?' chkON':'';
            output+='<li class="Industry' + i + flag + '" onclick="Industry.Chk(\''+i+'\')">'+ind_a[i]+'</li>';
        }
        for (var i in ind_flag_arr){
            output2+='<li class="Industry' + ind_flag_arr[i] + ' chkON" onclick="Industry.Chk(\''+ind_flag_arr[i]+'\')">'+ind_a[ind_flag_arr[i]]+'</li>';
        }
        jQuery('#drag').width('670px');
        jQuery('#IndustryList').html('<ul>'+output+'</ul>');
        jQuery('#IndustrySelected dd').html(output2);

        // 鼠标悬停变色
        jQuery('#IndustryAlpha li').hover(function(){jQuery(this).addClass('over')},function(){jQuery(this).removeClass('over')});
    },
    Chk : function(id){
        if(!in_array(id,ind_flag_arr)){
            if(ind_flag_arr.length<5){
                ind_flag_arr[ind_flag_arr.length]=id;
                var html='<li class="Industry'+id+'" onclick="Industry.Chk(\''+id+'\')">'+ind_a[id]+'</li>';
                jQuery('#IndustrySelected dd').append(html);
                jQuery('.Industry'+id).addClass('chkON');
                jQuery('#IndustrySelected li').hover(function(){jQuery(this).addClass('over')},function(){jQuery(this).removeClass('over')});
            }else{
                alert('您最多能选择5项');
                return false;
            }
        }else{
            for (var i in ind_flag_arr){
                if(ind_flag_arr[i]==id) ind_flag_arr.splice(i,1);;
            }
            jQuery('#IndustrySelected .Industry'+id).remove();
            jQuery('.Industry'+id).removeClass('chkON');
        }
    },
    // 确定
    confirm : function(){
        var indStr='';
        for(var i in ind_flag_arr){
            indStr+=','+ind_a[ind_flag_arr[i]];
        }
        indStr=indStr.substring(1)?indStr.substring(1):'请选择行业';
        jQuery('#btn_IndustryID').val(indStr);
        jQuery('#IndustryID').val(ind_flag_arr);
        boxAlpha();

    },

    /* ****************************** 单选 ********************************* */
    // 单选输出
    Show2 : function(){
        var output='',flag,output2='';
        output+='<table ><tbody style="border: 0px;">';
        for (var i in indcategory){
            if(i%2==0){
                output+='<tr bgcolor="#F6F6F6">';
            } else{
                output+='<tr>';
            }
            output+='<td style="width: 185px;font-size: 14px;padding-left: 6px;font-weight: bold;color: #4d963b;">'+indcategory[i][0]+'</td>';
            var ind_a_2 =indcategory[i][1];
            output+='<td style="width:720px;">'
            for (var j in ind_a_2){
                output+='<li onclick="Industry.Chk2(\''+ind_a_2[j]+'\')">'+ind_a[ind_a_2[j]]+'</li>';
            }
            output+='</td></tr>'
        }
        output+='</tbody></table>';
        jQuery('#drag').width('905px');

        jQuery('#IndustryList').html('<ul>'+output+'</ul>');
        // 鼠标悬停变色
        jQuery('#IndustryAlpha li').hover(function(){jQuery(this).addClass('over')},function(){jQuery(this).removeClass('over')});
    },
    Chk2 : function(id){
        jQuery('#'+ind_element_id).val(id);
        var inputObject = jQuery('#sel-'+ind_element_id);
        setSearchValue(inputObject, ind_a[id]);
        boxAlpha();
    }
}


// 多选
function IndustrySelect(){
    var dragHtml ='<div id="IndustryAlpha">';		//行业
    dragHtml+='		<dl id="IndustrySelected"><dt>已选行业：</dt><dd></dd></dl>';
    dragHtml+='		<div id="IndustryList"></div>';//行业列表
    dragHtml+='</div>';
    jQuery('#drag_h').html('<b>请选择行业（您最多能选择5项）</b><span onclick="Industry.confirm()">确定</span>');
    jQuery('#drag_con').html(dragHtml);

    Industry.Show();
    boxAlpha();
    draglayer();
}

// 单选
function IndustrySelect_2(elementId){
    ind_element_id = elementId;
    var dragHtml ='<div id="IndustryAlpha">';		//行业
    dragHtml+='		<div id="IndustryList" class="industry"></div>';//行业列表
    dragHtml+='</div>';
    jQuery('#drag_h').html('<b>请选择行业</b><span onclick="boxAlpha()">[关闭]</span> &nbsp; <span onclick="IndustryReset()">[不限]</span>');
    jQuery('#drag_con').html(dragHtml);

    Industry.Show2();
    boxAlpha();
    draglayer();
}

function IndustryReset(){
    jQuery('#'+ind_element_id).val('All');
    var inputObject = jQuery('#sel-'+ind_element_id);
    inputObject.val('不限');
    inputObject.attr('title','');
    boxAlpha();
}