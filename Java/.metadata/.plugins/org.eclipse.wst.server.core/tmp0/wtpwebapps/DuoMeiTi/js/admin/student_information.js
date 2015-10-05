


		
//delete
var delete_Id;
$(document).on("click", ".delete", function() {
	var temp = confirm("删除不可恢复！");
	if (temp == true) {
		delete_Id = $(this).parents("tr").attr("id");// attr所选元素属性值
		alert(delete_Id);
		
		$.ajax({
			url : 'student_manage_delete',
			type : 'post',
			dataType : 'json',
			data : {"rtID" : delete_Id,},// {"后台",""}
			success : deleteCallback
		});
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
	$.ajax({
		url : 'get_student_information',
		type : 'post',
		dataType : 'json',
		data : {"rtID" : edit_Id,},// {"后台",""}
		success : getInformationCallback
	});
})



function getInformationCallback(data) {

	/*alert(data.fullName);
	alert(data.isUpgradePrivilege);*/
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
