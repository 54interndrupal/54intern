var nation = {
	// �����
	Show : function(){
		var output='',flag,output2='';
		for (var i in na){
			output+='<li onclick="nation.Chk(\''+i+'\')">'+na[i]+'</li>';
		}
		$('#drag').width('370px');
		$('#nationList').html('<ul>'+output+'</ul>');
		// �����ͣ��ɫ
		$('#nationAlpha li').hover(function(){$(this).addClass('over')},function(){$(this).removeClass('over')});
	},
	Chk : function(id){
		$('#btn_nation').val(na[id]);
		$('#nation').val(id);
		boxAlpha();
	}
}

function nationSelect(){
	var dragHtml ='<div id="nationAlpha">';		//��
		dragHtml+='		<div id="nationList"></div>';//���б�
		dragHtml+='</div>';
	$('#drag_h').html('<b>��ѡ���</b><span onclick="boxAlpha()">�ر�</span>');
	$('#drag_con').html(dragHtml);

	nation.Show();
	boxAlpha();
	draglayer();
}