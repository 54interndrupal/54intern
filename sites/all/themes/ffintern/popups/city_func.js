var residency_hukou_flag=0;	// 居住地 / 户口所在地   开关
var residency_element_id;
var residency_auto_submit=false;
var residency = {
    // 居住地输出
    Show : function(){
        var k=0;
        var Div=new Array('maincity','allProv');
        while(k<=1){
            var output='<h4>主要城市：</h4>';
            var arr=maincity,area;
            if(k==1){
                output='<h4>其他省市：</h4>';
                arr=allprov;
            }
            for (var i in arr){
                area=arr[i][0];
                output+='<dl><dt>'+area+'</dt><dd>';
                for (var j in arr[i][1] ){
                    id=arr[i][1][j];
                    if(k==0){
                        output+='<li onclick="residency.Chk(\''+id+'\')">'+ja[id]+'</li>';
                    }else{
                        if(area=='其它') output+='<li onclick="residency.Chk(\''+id+'\')">'+ja[id]+'</li>';
                        else output+='<li onclick="residency.SubLayer(\''+id+'\')">'+ja[id]+'</li>';
                    }
                }
                output+='</dd></dl>';
            }
            jQuery('#'+Div[k]).html(output);
            k++;
        }
        jQuery('#drag').width('542px');
        // 鼠标悬停变色
        jQuery('#residencyAlpha li').hover(function(){jQuery(this).addClass('over')},function(){jQuery(this).removeClass()});
        // 点击弹出子菜单
        if(jQuery('.toolbar').size()>=1){
            jQuery('#allProv li').click(function(e){jQuery("#sublist").css({top:e.pageY-4-150,left:e.pageX-50}).hover(function(){jQuery(this).show()},function(){jQuery(this).hide()})})
        }else{
            jQuery('#allProv li').click(function(e){jQuery("#sublist").css({top:e.pageY-4,left:e.pageX-4}).hover(function(){jQuery(this).show()},function(){jQuery(this).hide()})})
        }


    },
    // 所有省份 下拉 城市菜单
    SubLayer : function(id){
        var output='<div id="sub_city">',width,ischecked,key;
        var arr=getAreaIDs(id);
        width=Math.ceil(Math.sqrt(arr.length-1))*60;
        output+='<ul style="width:'+width+'px"><h4 onclick="residency.Chk(\''+id+'\')"><a href="javascript:">'+ja[id]+'</a></h4>';
        for (var i=1;i<arr.length;i++){
            key=arr[i];
            output+='<li><a href="javascript:" onclick="residency.Chk(\''+key+'\')">'+ja[key]+'</a></li>';
        }
        output=output+'</ul></div>';
        jQuery("#sublist").html(output).show();
    },


    Chk : function(id){
        jQuery('#'+residency_element_id).val(id);
        jQuery('#sel-'+residency_element_id).val(ja[id]);
        jQuery("#sublist").hide().empty();
        boxAlpha();
        if(residency_auto_submit){
            jQuery('#edit-submit-jobs').click();
        }
    }
}

function residencySelect(elementId, autoSubmit){
    if(!autoSubmit){
        residency_auto_submit = false;
    }else{
        residency_auto_submit = autoSubmit;
    }
    residency_element_id = elementId;
    residency_hukou_flag=0;
    var dragHtml ='<div id="residencyAlpha">';		//居住地
    dragHtml+='		<div id="maincity"></div>';	//主要城市
    dragHtml+='		<div id="allProv"></div>';	//所有省市
    dragHtml+='</div>';
    jQuery('#drag_h').html('<b>请选择所在地</b><span onclick="boxAlpha()">[关闭]</span>&nbsp; <span onclick="jobAreaReset()">[不限]</span>');
    jQuery('#drag_con').html(dragHtml);
    residency.Show();
    boxAlpha();
    draglayer();
}
function hukouSelect(){
    residency_hukou_flag=1;
    var dragHtml ='<div id="residencyAlpha">';		//居住地
    dragHtml+='		<div id="maincity"></div>';	//主要城市
    dragHtml+='		<div id="allProv"></div>';	//所有省市
    dragHtml+='</div>';
    jQuery('#drag_h').html('<b>请选择户口所在地</b><span onclick="boxAlpha()">关闭</span>');
    jQuery('#drag_con').html(dragHtml);
    residency.Show();
    boxAlpha();
    draglayer();
}


/* **************************************************************************** */

var jobArea_Arr = new Array();
//var jobArea_Arr = new Array('0100','0200','2402');

var jobArea = {
    // 请选择地区
    init : function(){
        var _str='',_id='';
        if (jobArea_Arr.length>0){
            for (var i in jobArea_Arr){
                _str+=','+ja[jobArea_Arr[i]];
                _id+=','+jobArea_Arr[i];
            }
            jQuery('#btn_jobArea').val(_str.substring(1));
            jQuery('#jobAreaID').val(_id.substring(1));
        }
    },
    Show : function(){
        var k=0,output='',output2='',arr,area,select_ed;
        var Div		= new Array('maincity2','allProv2');
        var Title	= new Array('<h4>主要城市：</h4>','<h4>所有省份：</h4>');
        var LoopArr	= new Array(maincity,allprov);

        for(var i in jobArea_Arr){
            output2+='<li class="jobArea'+jobArea_Arr[i]+' chkON" onclick="jobArea.Chk(\''+jobArea_Arr[i]+'\')">'+ja[jobArea_Arr[i]]+'</li>';
        }
        jQuery('#jobAreSelected dd').html(output2);

        while(k<=1){
            output	= Title[k];
            arr		= LoopArr[k]
            for (var i in arr){
                area=arr[i][0];
                output+='<dl><dt>'+area+'</dt><dd>';
                for (var j in arr[i][1] ){
                    id=arr[i][1][j];
                    if(k==0){
                        select_ed=in_array(id,jobArea_Arr)?' chkON':'';
                        output+='<li class="jobArea'+id+select_ed+'" onclick="jobArea.Chk(\''+id+'\')">'+ja[id]+'</li>';
                    }else{
                        if(area=='其它') output+='<li class="jobArea'+id+'" onclick="jobArea.Chk(\''+id+'\')">'+ja[id]+'</li>';
                        else output+='<li onclick="jobArea.SubLayer(\''+id+'\')">'+ja[id]+'</li>';
                    }
                }
                output+='</dd></dl>';
            }

            jQuery('#'+Div[k]).html(output);
            k++;
        }
        jQuery('#drag').width('580px');
        // 鼠标悬停变色
        jQuery('#jobAreaAlpha li').hover(function(){jQuery(this).addClass('over')},function(){jQuery(this).removeClass('over')});
        // 点击弹出子菜单
        if(jQuery('.toolbar').size()==1){
            jQuery('#allProv2 li').click(function(e){jQuery("#sublist").css({top:e.pageY-4-150,left:e.pageX-4}).hover(function(){jQuery(this).show()},function(){jQuery(this).hide()})})
        }else{
            jQuery('#allProv2 li').click(function(e){jQuery("#sublist").css({top:e.pageY-4,left:e.pageX-4}).hover(function(){jQuery(this).show()},function(){jQuery(this).hide()})})
        }

    },
    // 所有省份 下拉 城市菜单
    SubLayer : function(id){
        var output='<div id="sub_jobArea">',width,select_ed,key;
        select_ed=in_array(id,jobArea_Arr)?' chkON':'';
        var arr=getAreaIDs(id);
        width=Math.ceil(Math.sqrt(arr.length-1))*60;
        output+='<ul style="width:'+width+'px"><h4 onclick="jobArea.Chk(\''+id+'\')">';
        output+='<a href="javascript:" class="jobArea' + id + select_ed +'">'+ja[id]+'</a></h4>';

        for (var i=1;i<arr.length;i++){
            key=arr[i];
            select_ed=in_array(key,jobArea_Arr)?' chkON':'';
            output+='<li><a href="javascript:" class="jobArea' + key + select_ed +'" onclick="jobArea.Chk(\''+key+'\')">'+ja[key]+'</a></li>';
        }
        output=output+'</ul></div>';
        jQuery("#sublist").html(output).show();
    },


    Chk : function(id){
        if(!in_array(id,jobArea_Arr)){
            var subArea,myid;
            if(id.substr(2)=='00'){	// 选中父类清除子类
                subArea=getAreaIDs(id);
                for(var i in subArea){
                    if(in_array(subArea[i],jobArea_Arr)) this.del(subArea[i]);
                }
            }else{	// 选中子类清除父类
                myid=id.substr(0,2)+'00';
                if(in_array(myid,jobArea_Arr)) this.del(myid);
            };
            if(jobArea_Arr.length<5){
                jobArea_Arr[jobArea_Arr.length]=id;
                var html='<li class="jobArea'+id+'" onclick="jobArea.Chk(\''+id+'\')">'+ja[id]+'</li>';
                jQuery('#jobAreSelected dd').append(html);
                jQuery('.jobArea'+id).addClass('chkON');
                jQuery('#jobAreSelected li').hover(function(){jQuery(this).addClass('over')},function(){jQuery(this).removeClass('over')});
            }else{
                alert('您最多能选择5项');
                return false;
            }
        }else{
            this.del(id);
        }
    },
    del : function(id){
        for (var i in jobArea_Arr){
            if(jobArea_Arr[i]==id) jobArea_Arr.splice(i,1);;
        }
        jQuery('#jobAreSelected .jobArea'+id).remove();
        jQuery('.jobArea'+id).removeClass('chkON');
    },
    // 确定
    confirm : function(){
        var areaStr='';
        for(var i in jobArea_Arr){
            areaStr+=','+ja[jobArea_Arr[i]];
        }
        areaStr=areaStr.substring(1)?areaStr.substring(1):'请选择地区';
        jQuery('#btn_jobArea').val(areaStr);
        jQuery('#jobAreaID').val(jobArea_Arr);
        boxAlpha();
        jQuery('#jobAreSelected dd').empty();
    }
}

function jobAreaSelect(){
    var dragHtml ='<div id="jobAreaAlpha">';		//地区
    dragHtml+='		<dl id="jobAreSelected"><dt>已选地点：</dt><dd></dd></dl>';
    dragHtml+='		<div id="maincity2"></div>';//主要城市
    dragHtml+='		<div id="allProv2"></div>';	//所有省市
    dragHtml+='</div>';
    jQuery('#drag_h').html('<b>请选择地区（您最多能选择5项）</b><span onclick="jobArea.confirm()">确定</span>');
    jQuery('#drag_con').html(dragHtml);

    jobArea.Show();
    boxAlpha();
    draglayer();
}

function jobAreaReset(){
    jQuery('#'+residency_element_id).val('All');
    var inputObject = jQuery('#sel-'+residency_element_id);
    inputObject.val('不限');
    inputObject.attr('title','');
    boxAlpha();
}