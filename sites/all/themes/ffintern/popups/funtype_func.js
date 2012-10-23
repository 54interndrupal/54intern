var fun_flag_arr = new Array();		//	已选中数组
var fun_element_id;
//var fun_flag_arr = new Array('0100','2400','2402');

var Funtype = {
    // 职位列表
    init : function(){
        var _str='',_id='';
        if (fun_flag_arr.length>0){
            for (var i in fun_flag_arr){
                _str+=','+fun_a[fun_flag_arr[i]];
                _id+=','+fun_flag_arr[i];
            }
            jQuery('#'+fun_element_id).val(_str.substring(1));
            jQuery('#sel-'+fun_element_id).val(_id.substring(1));
        }
    },
    Show : function(){
        var output='',flag,output2='';
        for(var i in fun_flag_arr){
            output2+='<li class="Funtype'+fun_flag_arr[i]+' chkON" onclick="Funtype.Chk(\''+fun_flag_arr[i]+'\')">'+fun_a[fun_flag_arr[i]]+'</li>';
        }
        jQuery('#FuntypeSelected dd').html(output2);

        for (var i in funcategory){
            output+='<li>'+funcategory[i][0]+'</li>';
            var fun_a_2 =funcategory[i][1];
            for (var j in fun_a_2){

                output+='<li onclick="Funtype.SubLayer(\''+i+'\')">'+fun_a_2[i]+'</li>';

            }
        }


        jQuery('#drag').width('670px');
        jQuery('#FuntypeList').html('<ul>'+output+'</ul>');
        jQuery('#FuntypeSelected dd').html(output2);

        // 鼠标悬停变色
        jQuery('#FuntypeAlpha li').hover(function(){jQuery(this).addClass('over')},function(){jQuery(this).removeClass('over')});
        // 点击弹出子菜单
        jQuery('#FuntypeList li').click(function(e){jQuery("#sublist").css({top:e.pageY-4,left:e.pageX-4}).hover(function(){jQuery(this).show()},function(){jQuery(this).hide()})})
    },
    // 子职位 悬浮菜单
    SubLayer : function(id){
        var output='',width,flag;
        var myid=id.substr(0,2);
        var len=0;
        for (var i in fun_a){
            if(i.substr(0,2)==myid){
                flag=in_array(i,fun_flag_arr)?' chkON':'';
                if(i.substr(2)=='00'){
                    output+='<h4 onclick="Funtype.Chk(\''+id+'\')"><a href="javascript:" class="Funtype' + id + flag +'">'+fun_a[id]+'</a></h4>';
                }else{
                    output+='<li><a href="javascript:" class="Funtype' + i + flag +'" onclick="Funtype.Chk(\''+i+'\')">'+fun_a[i]+'</a></li>';
                    len++;
                }
            }
        }
        width=len>10?440:220;
        output='<div id="sub_funtype"><ul style="width:'+width+'px">'+output+'</ul></div>';
        jQuery("#sublist").html(output).show();
    },
    Chk : function(id){
        if(!in_array(id,fun_flag_arr)){
            if(id.substr(2)=='00'){	// 选中父类清除子类
                for (var i in fun_a){
                    if(i.substr(0,2)==id.substr(0,2)){
                        if(in_array(i,fun_flag_arr)) this.del(i);
                    }
                }
            }else{	// 选中子类清除父类
                var myid;
                myid=id.substr(0,2)+'00';
                if(in_array(myid,fun_flag_arr)) this.del(myid);
            };

            if(fun_flag_arr.length<5){
                fun_flag_arr[fun_flag_arr.length]=id;
                var html='<li class="Funtype'+id+'" onclick="Funtype.Chk(\''+id+'\')">'+fun_a[id]+'</li>';
                jQuery('#FuntypeSelected dd').append(html);
                jQuery('.Funtype'+id).addClass('chkON');
                jQuery('#FuntypeSelected li').hover(function(){jQuery(this).addClass('over')},function(){jQuery(this).removeClass('over')});
            }else{
                alert('您最多能选择5项');
                return false;
            }
        }else{
            this.del(id)
        }
    },
    del : function(id){
        for (var i in fun_flag_arr){
            if(fun_flag_arr[i]==id) fun_flag_arr.splice(i,1);;
        }
        jQuery('#FuntypeSelected .Funtype'+id).remove();
        jQuery('.Funtype'+id).removeClass('chkON');
    },
    // 确定
    confirm : function(){
        var funStr='',fun_Id='';
        for(var i in fun_flag_arr){
            funStr+=','+fun_a[fun_flag_arr[i]];
        }
        funStr=funStr.substring(1)?funStr.substring(1):'请选择职能类别';
        jQuery('#btn_FuntypeID').val(funStr);
        jQuery('#FuntypeID').val(fun_flag_arr);
        boxAlpha();
    },


    /* ****************************** 单选 ********************************* */
    // 单选输出
    Show2 : function(){
        var output='',flag,output2='';
        output+='<table ><tbody style="border: 0px;">';
        for (var i in funcategory){
            if(i%2==0){
                output+='<tr bgcolor="#F6F6F6">';
            } else{
                output+='<tr>';
            }
            output+='<td style="width: 185px;font-size: 14px;padding-left: 3px;font-weight: bold;color: #4d963b;">'+funcategory[i][0]+'</td>';
            var fun_a_2 =funcategory[i][1];
            output+='<td style="width: 540px;">'
            for (var j in fun_a_2){
                output+='<li onclick="Funtype.SubLayer2(\''+fun_a_2[j]+'\')">'+fun_a[fun_a_2[j]]+'</li>';
            }
            output+='</td></tr>'
        }
        output+='</tbody></table>';
        jQuery('#drag').width('760px');
        jQuery('#FuntypeList').html('<ul>'+output+'</ul>');
        // 鼠标悬停变色
        jQuery('#FuntypeAlpha li').hover(function(){jQuery(this).addClass('over')},function(){jQuery(this).removeClass('over')});
        // 点击弹出子菜单
        jQuery('#FuntypeList li').click(function(e){jQuery("#sublist").css({top:e.pageY-4,left:e.pageX-4}).hover(function(){jQuery(this).show()},function(){jQuery(this).hide()})})
    },
    // 子职位 悬浮菜单
    SubLayer2 : function(id){
        var output='',width;
        var myid=id.substr(0,2);
        var len=0;
        for (var i in fun_a){
            if(i.substr(0,2)==myid){
                if(i.substr(2)=='00'){
                    output+='<h4 onclick="Funtype.Chk2(\''+id+'\')"><a href="javascript:">'+fun_a[id]+'</a></h4>';
                }else{
                    output+='<li><a href="javascript:" onclick="Funtype.Chk2(\''+i+'\')">'+fun_a[i]+'</a></li>';
                    len++;
                }
            }
        }
        width=len>10?400:200;
        output='<div id="sub_funtype" class="radio"><ul style="width:'+width+'px">'+output+'</ul></div>';
        jQuery("#sublist").html(output).show();
    },
    Chk2 : function(id){
        jQuery('#'+fun_element_id).val(id);
        var inputObject = jQuery('#sel-'+fun_element_id);
        setSearchValue(inputObject, fun_a[id]);
        jQuery("#sublist").empty().hide();
        boxAlpha();
    }
}

// 多选
function funtypeSelect(){
    var dragHtml ='<div id="FuntypeAlpha">';			//职能类别
    dragHtml+='		<dl id="FuntypeSelected"><dt>已选职能类别：</dt><dd></dd></dl>';
    dragHtml+='		<div id="FuntypeList"></div>';	//职能类别列表
    dragHtml+='</div>';
    jQuery('#drag_h').html('<b>请选择职能类别（您最多能选择5项）</b><span onclick="Funtype.confirm()">确定</span>');
    jQuery('#drag_con').html(dragHtml);

    Funtype.Show();
    boxAlpha();
    draglayer();
}

// 单选
function funtypeSelect_2(elementId){
    fun_element_id =  elementId;
    var dragHtml ='<div id="FuntypeAlpha">';			//职能类别
    dragHtml+='		<div id="FuntypeList"></div>';	//职能类别列表
    dragHtml+='</div>';
    jQuery('#drag_h').html('<b>请选择职能类别</b><span onclick="boxAlpha()">[关闭]</span> &nbsp; <span onclick="funtypeReset()">[不限]</span>');
    jQuery('#drag_con').html(dragHtml);
    Funtype.Show2();
    boxAlpha();
    draglayer();
}

function funtypeReset(){
    jQuery('#'+fun_element_id).val('All');
    var inputObject = jQuery('#sel-'+fun_element_id);
    inputObject.val('不限');
    inputObject.attr('title','');
    boxAlpha();
}