/**
 * 
 */



$("#envelope").click(function(){
	var list_box=$("#message-list-box");
	var content_box=$("#message-content-box");
	var contacts_box=$("#message-contacts-box");
	if(list_box.hasClass("hide")&&content_box.hasClass("hide")&&contacts_box.hasClass("hide")){
		message_list_box_show();
	}
	else{
		message_contacts_box_hide();
		message_list_box_hide();
		message_content_box_hide();
	}
})

$(".contacts-list-group").on("click","li",function(){
	var contentBox=$("#message-content-box");
	contentBox.attr("iid",$(this).attr("id"));
	$(".message-content-top .title").html($(this).html());
	message_list_box_hide();
	message_content_box_show();
});

$(".message-list").on("click","li",function(){
	var contentBox=$("#message-content-box");
	contentBox.attr("iid",$(this).attr("fid"));
	$(".message-content-top .title").html($(this).attr("fname"));
	message_list_box_hide();
	message_content_box_show();
})
	

function userlistCallback(data){
	var adminList=data.adminList;
	var studentList=data.studentList;
	var adminListBox=$("#admin-contacts ul");
	var teacherListBox=$("#teacher-contacts ul");
	var studentListBox=$("#student-contacts ul");
	$(adminList).each(function(i){
		adminListBox.append('<li class="list-group-item" id="'+adminList[i].id+'">'+adminList[i].username+'</li>');
	})
	$(studentList).each(function(i){
		studentListBox.append('<li class="list-group-item" id="'+studentList[i].id+'">'+studentList[i].username+'</li>');
	})
}

function message_list_box_show(){
	$("#message-list-box").removeClass("hide");
	var contentBox=$("#message-content-box");
	var from=contentBox.attr("from");
	$.ajax({
		url:"/message/getNewMessage",
		type : 'post',
		dataType : 'json',
		data : {"currentUser":from},
		success : getNewMessageCallBack
	})
}

function getNewMessageCallBack(data){
	var messageList=data.newMes;
	var messageListBox=$(".message-list");
	messageListBox.html(data.messageListHtml);
}

function message_list_box_hide(){
	$("#message-list-box").addClass("hide");
}
function message_contacts_box_show(){
	var box=$("#message-contacts-box");
	if(box.hasClass("hide")){
		box.removeClass("hide");
		$.ajax({
			url : '/message/userlist',
			type : 'post',
			dataType : 'json',
			data : {},
			success : userlistCallback
		});
	}
}
function message_contacts_box_hide(){
	$("#message-contacts-box").addClass("hide");
	$("#admin-contacts ul").html("");
	$("#teacher-contacts ul").html("");
	$("#student-contacts ul").html("");
}
function message_content_box_show(){
	var contentBox=$("#message-content-box");
	var id=contentBox.attr("iid");
	$.ajax({
		url:"/message/getMessage",
		type:"post",
		dataType:"json",
		data:{"another":id},
		success:getMessageCallback
	});
	contentBox.removeClass("hide");
}

function getMessageCallback(data){
	var contentBox=$(".message-content");
	contentBox.html(data.historyMesHtml);
}

function message_content_box_hide(){
	$("#message-content-box").addClass("hide");
}

$("#message-list-box .closed").click(function(){
	message_list_box_hide();
	message_contacts_box_hide();
})

$("#write-message").click(function(){
	message_content_box_show();
	message_list_box_hide();
	message_contacts_box_show();
})

$("#message-content-box .closed").click(function(){
	message_content_box_hide();
	message_contacts_box_hide();
})

$("#message-content-box .back").click(function(){
	message_content_box_hide();
	message_list_box_show();
})

$("#message-contacts-box .closed").click(function(){
	message_contacts_box_hide();
})

$(".users").click(function(){ 
	message_contacts_box_show();
})

$(".contacts-expand").click(function(){
	var s=$(this).children("span");
	if(s.hasClass("glyphicon-plus")){
		s.removeClass("glyphicon-plus");
		s.addClass("glyphicon-minus");
	}
	else{
		s.removeClass("glyphicon-minus");
		s.addClass("glyphicon-plus");
	}
	
})

//////////////////////////////////////////////////////////////////

function longPolling(){
	$.ajax({
		url:"/message/longpolling",
		type:"POST",
		datatype:"json",
		data:"",
		success:reciveData,
		error:errorProcess,
	})
}

function reciveData(data){
	
}

function errorProcess(data){
	
}

function sendMessage(){
	var contentBox=$("#message-content-box");
	var to=contentBox.attr("iid");
	var from=contentBox.attr("from");
	var textBoard=$(".message-writeboard textarea");
	var mesContent=textBoard.val();
	textBoard.val("");
	$("#message-content-box .message-content").append('<div class="message clearfix"><span class="triangle"></span>\
            <div class="article">'+mesContent+'</div></div>');
	
	var param={
		"from":from,
		"to":to,
		"content":mesContent
	}
	
	$.ajax({
		url:"/message/receiveMes",
		type:"POST",
		dataType : 'json',
		data:param,
		success:sendMessageCallBack,
	})
}

function sendMessageCallBack(data){
//	if(data.error!="")alert(data.error);
}