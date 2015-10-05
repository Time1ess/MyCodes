/**
 * 
 */
function GetRequest() {
	//url例子：XXX.aspx?ID=" + ID + "&Name=" + Name；  
	var url = location.search; //获取url中"?"符以及其后的字串  
	var theRequest = new Object();
	if (url.indexOf("?") != -1)//url中存在问号，也就说有参数。  
	{
		var str = url.substr(1);
		strs = str.split("&");
		for (var i = 0; i < strs.length; i++) {
			theRequest[strs[i].split("=")[0]] = unescape(strs[i].split("=")[1]);
		}
	}
	return theRequest;
}

//jquery发送ajax请求
function queryclassrooms() {
	//var params = $('#classroom_search_form').serialize(); //利用jquery将表单序列化
	//params = decodeURIComponent(params,true);
	$("#pagediv").css("display","none");
	var searchselect = $("#searchselect  option:selected").attr("value");
	var query_condition = $("#query_condition").val();
	var Request = new Object();
	//获取url中的参数  
	Request = GetRequest();
	var build_id = Request['build_id'];
	var build_name = Request['build_name'];
	var params = {
		"searchselect" : searchselect,
		"query_condition" : query_condition,
		"build_id" : build_id,
		"build_name" : build_name
	};
	
	$.ajax({
		url : '/admin/classroom_json/classroom_search',
		type : 'post',
		dataType : 'json',
		data : params,
		success : ClassroomSearchCallback
	});
}

function ClassroomSearchCallback(data) {
	if (data.status == "0") {
		$("#classroom_table tr:not(:first)").remove();
		$("#classroom_table tr:first").after(data.classroominfo_html);
		var classrooms = data.classrooms;
		var table = $("#classroom_search_table");
		var row;
		$(classrooms).each(function(i) {
			row = $(table).find("tr:eq(" + (i + 1) + ")");
			$(row).find("td:eq(0)").text(classrooms[i].classroom_num);
			$(row).find("td:eq(1)").text(classrooms[i].repertorys);
//			$(row).find("td:eq(2)").text(classrooms[i].capacity);
			$(row).find("td:eq(2)").text(classrooms[i].principal_name);
			$(row).find("td:eq(3)").children().eq(0).attr("onclick", "edit_classroom("+ i +")");
			$(row).find("td:eq(4)").children().eq(0).attr("href", "classroom_detail?classroom_id=" + classrooms[i].id +"&classroom_num=" +classrooms[i].classroom_num);
		});
	} else if (data.status == "1") {
		animatedShow("查询关键字为空");
	} 
}

function queryAll() {
	$("#pagediv").css("display","block");
	$("#query_condition").val("");
	//获取url中的参数  
	Request = GetRequest();
	var build_id = Request['build_id'];
	var build_name = Request['build_name'];
	var params = {
		"searchselect" : "",
		"query_condition" : "",
		"build_id" : build_id,
		"build_name" : build_name
	};
	
	$.ajax({
		url : '/admin/classroom_json/classroom_search',
		type : 'post',
		dataType : 'json',
		data : params,
		success : ClassroomSearchCallback
	});
}


function disable_add_btn() {
	$("#add_classroom_btn").attr("disabled", "disabled");
}



function query_stu_name() {
	$('#classroom-modal').modal({
		backdrop: 'static', 
		keyboard: false
 	});
	var input_principal_student_id = $("#input_principal_student_id").val();
	if(input_principal_student_id == "" || !/^\d+$/.test(input_principal_student_id)) {
		$("#input_principal_student_name").text("请输入数字!");
		return;
	}
	
	$.ajax({
		url : '/admin/classroom_json/queryStuNameByStuId',
		type : 'post',
		dataType : 'json',
		data : {
			"stuId" : input_principal_student_id
		},
		success : queryStuNameCallback
	});
}
function queryStuNameCallback(data) {
	if(data.queryResult==null || data.queryResult == "") {
		$("#input_principal_student_name").text("无此学号!");
		$("#add_classroom_btn").attr("disabled", "disabled");
	}
	else {
		$("#input_principal_student_name").text(data.queryResult);
		$("#add_classroom_btn").removeAttr("disabled");
	}
}





function classroom_submit() {
	var submit_type = $("#submit_type").attr("value");
//	alert(submit_type);
	var stuId = $("#input_principal_student_id").val();
	var classroom_num = $("#input_classroom_num").val();
		
	Request = GetRequest();
	var build_id = Request['build_id'];
//	alert(stuId + " " +classroom_num + " " + build_id);
	$.ajax({
		url : '/admin/classroom_json/addClassroom',
		type : 'post',
		dataType : 'json',
		data : {
			"stuId" : stuId,
			"add_classroom_num" : classroom_num,
			"build_id" : build_id,
			"submit_type" : submit_type
		},
		success : addClassroomCallback
	});
}
function addClassroomCallback(data) {
	if(data.add_status == "exist") {
		$("#exist").text("教室号已存在");
	}
	else if(data.add_status == "ok") {
		$('#classroom-modal').modal('hide');
		window.location.href=window.location.href;  
		window.location.reload;
	}
}

function dismiss() {
	$('#classroom-modal').on('hidden.bs.modal', function (e) {
		$("#exist").text("");
	});
}

function add_classroom() {
	$("#input_principal_student_id").val("");
	$("#input_principal_student_name").text("");
	$("#input_classroom_num").val("");
	
	$("#submit_type").attr("value", "add");
	$("#add_classroom_btn").text("确定添加");
	$('#classroom-modal').modal('show');
	
	dismiss();
}

function edit_classroom(index) {
	var select_classroom_num = $("#classroom_search_table").find("tr:eq(" + (index + 1) + ") td:eq(0)").text();
	var select_stu_td = $("#classroom_search_table").find("tr:eq(" + (index + 1) + ") td:eq(2)");
	var select_studId = $(select_stu_td).attr("studId");
	var select_stuName = $(select_stu_td).text();
//	alert(index +" "+"  "+select_classroom_num +" "+select_studId+" "+select_stuName);
	
	select_classroom_num = select_classroom_num.trim();
	select_studId = select_studId.trim();
	
	$("#input_principal_student_id").val(select_studId);
	$("#input_principal_student_name").text(select_stuName);
	$("#input_classroom_num").val(select_classroom_num);
	
	$("#submit_type").attr("value", "update");
	$("#add_classroom_btn").text("确定更新");
	$('#classroom-modal').modal('show');
	
	dismiss();
}


/* function mypost(count) {
	var xmlobj; //定义XMLHttpRequest对象 
	//如果当前浏览器支持Active Xobject，则创建ActiveXObject对象  
	if (window.ActiveXObject) {
		//xmlobj = new ActiveXObject("Microsoft.XMLHTTP");  
		try {
			xmlobj = new ActiveXObject("Msxml2.XMLHTTP");
		} catch (e) {
			try {
				xmlobj = new ActiveXObject("Microsoft.XMLHTTP");
			} catch (E) {
				xmlobj = false;
			}
		}
	}
	//如果当前浏览器支持XMLHttp Request，则创建XMLHttpRequest对象  
	else if (window.XMLHttpRequest) {
		xmlobj = new XMLHttpRequest();
	}
	
	var pageSize = $("#pageSize").text();
	Request = GetRequest();
	var currPage = Request['currPage'];
	if(currPage == null) currPage = 1;
	var index = (currPage - 1) * pageSize + count;
	//return index;
	// alert(index);
	var build_name = $("#build_name").text();
	var param = "classroomselectIndex=" + index + "&build_name=" + build_name;
	
	xmlobj.open("POST", "/admin/classroom/classroom_detail", true); //调用classroom_detail.action     
	xmlobj.setRequestHeader("cache-control", "no-cache");
	xmlobj.setRequestHeader("contentType", "text/html;charset=uft-8"); //指定发送的编码  
	xmlobj.setRequestHeader("Content-Type",
			"application/x-www-form-urlencoded;"); //设置请求头信息  

	xmlobj.send(param); //设置为发送给服务器数据 
	window.location.href = "/admin/classroom/classroom_detail?classroomselectIndex=" + index + "&build_name=" + build_name;
} */