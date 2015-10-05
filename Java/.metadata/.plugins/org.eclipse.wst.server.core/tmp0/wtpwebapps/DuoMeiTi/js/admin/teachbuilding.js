/**
 * 
 */
function add() {
	$('#teachBuildingModal').modal('show');
	
	$('#teachBuildingModal').on('hidden.bs.modal', function (e) {
		$("#exist").text("");
	});
}

function addTeachBuilding() {
	var input_buildName_num = $("#input_buildName_num").val();
	$.ajax({
		url : '/admin/classroom_json/addTeachBuilding',
		type : 'post',
		dataType : 'json',
		data : {
			"build_name" : input_buildName_num
		},
		success : addTeachBuildingCallback
	});
}

function addTeachBuildingCallback(data) {
	if(data.add_status == "exist") {
		$("#exist").text("教室号已存在");
	}
	else if(data.add_status == "ok") {
		$('#teachBuildingModal').modal('hide');
		window.location.href=window.location.href;  
		window.location.reload;
	}
}