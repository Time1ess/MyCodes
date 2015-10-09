

//search
var name_id;
$(document).on("click", "#student_search", function() {
	name_id = $("#name_id").val();
	search_select = $("#search_select").val();
/*	alert("检索2:" + name_id + search_select);*/
	var params = {
			"search_select" : search_select,
			"name_id" : name_id,
		};
	
	$.ajax({
        url: 'student_information_search',
        type: 'post',
        dataType: 'json',
        data : params,
        success: searchCallback
      });
})

var search_student;
function searchCallback(data) {
	var student_list = data.student_list;
	var tb = document.getElementById('student_information_table');
	var rowNum=tb.rows.length;
	
	if(data.isEmpty == "1"){
		search_student = data.student_profile_id;
		/*alert("查询成功！" + search_student );*/
		for (i=2; i<rowNum; i++)
	    {
	        tb.deleteRow(i);
	        rowNum=rowNum-1;
	        i=i-1;
	    }
		document.getElementById('search_information').style.display='';
		search_name.innerText = data.fullName; 
		search_studentid.innerText = data.studentId;
		search_college.innerText = data.college;
		search_number.innerText = data.phoneNumber;
		if(data.isUpgradePrivilege == 1)
		{
			search_isUpgradePrivilege.innerText = "管理教师";
		}
		else{
			search_isUpgradePrivilege.innerText = "在职学生";
		}
	}	
	else{
		alert("查找的学生不存在！");
		location.reload();
	}
	/*alert("OK!");*/
	

}


//delete
var delete_Id;
$(document).on("click", ".delete", function() {
	var temp = confirm("删除不可恢复！");
	if (temp == true) {
		delete_Id = $(this).parents("tr").attr("id");// attr所选元素属性值
		/*alert(delete_Id);*/
		if(delete_Id == "search_information"){
			alert(search_student);
			$.ajax({
				url : 'student_manage_delete',
				type : 'post',
				dataType : 'json',
				data : {"rtID" : search_student,},// {"后台",""}
				success : deleteCallback
			});
		}
		else{
			$.ajax({
				url : 'student_manage_delete',
				type : 'post',
				dataType : 'json',
				data : {"rtID" : delete_Id,},// {"后台",""}
				success : deleteCallback
			});
		}
	}
})

function deleteCallback(data) {
	location.reload() 
	alert("删除成功！");
}



//edit
var edit_Id;
$(document).on("click", ".edit", function() {

	edit_Id = $(this).parents("tr").attr("id");// attr所选元素属性值
	if(edit_Id == "search_information"){
		/*alert("编辑：" + search_student);*/
		$.ajax({
			url : 'get_student_information',
			type : 'post',
			dataType : 'json',
			data : {"rtID" : search_student,},// {"后台",""}
			success : getInformationCallback
		});
	}
	
	else{
		/*alert("id：" + edit_Id);*/
		$.ajax({
			url : 'get_student_information',
			type : 'post',
			dataType : 'json',
			data : {"rtID" : edit_Id,},// {"后台",""}
			success : getInformationCallback
		});
	}
})



function getInformationCallback(data) {

	/*alert(data.fullName);
	alert("getInformationCallback");*/
	$("#fullName").val(""+data.fullName);
	$("#studentId").val(""+data.studentId);
	$("#college").val(""+data.college);
	$("#phoneNumber").val(""+data.phoneNumber);
	$("#isUpgradePrivilege").val(""+data.isUpgradePrivilege);
	
}


//save
$(document).on("click", "#editSave", function() {
	/*alert("save");*/
	var params = $('#edit_student_form').serialize(); //利用jquery将表单序列化 
	/*alert(params);*/
	$.ajax({
        url: 'student_information_save',
        type: 'post',
        dataType: 'json',
        data: params,
        success: studentInformationSaveCallback
      });
	
})

function studentInformationSaveCallback() {
	$('#student_edit').modal('hide');
	location.reload() 
	alert("修改成功！");
	
}
