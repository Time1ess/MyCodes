//insert
function cleanValue() {
	$("[name=rtDevice]").val("");
	$("#rtType1").hide();
	$("#rtType2").hide();
	$("#filterclean").hide();
	$("#freq").hide();
	$("[name=rtType]").val("");
	$("[name=rtNumber]").val("");
	$("[name=rtVersion]").val("");
	$("[name=rtProdDate]").val("");
	$("[name=rtApprDate]").val("");
	$("[name=rtFactorynum]").val("");
	$("[name=rtDeviceStatus]").val("");
	$("[name=rtReplacePeriod]").val("");
	$("[name=rtFilterCleanPeriod]").val("");
	$("[name=rtFreqPoint]").val("");
}

$(document).on("click", "#rtInsert", function() {
	cleanValue();
	$("#rtSave").attr("mark","insert");
	$("#modal-title").html("添加设备信息");
})

$(document).find("#rtDevice").change(function() {
	var selectvalue = $("#rtDevice option:selected").attr("value");
	if(selectvalue == ""){
		$("#rtType1").hide();
		$("#rtType2").hide();
	} else if (selectvalue == "主要设备") {
		$("#rtType1").show();
		$("#rtType2").hide();
	} else if (selectvalue == "耗材设备") {
		$("#rtType2").show();
		$("#rtType1").hide();
	}
})
$(document).find("#rtType1").change(function() {
	var svalue = $("#rtType1 option:selected").attr("value");
	if(svalue == "投影机") {
		$("#filterclean").show();
		$("#freq").hide();
	}
	else if(svalue == "麦克") {
		$("#filterclean").hide();
		$("#freq").show();
	}
	else {
		$("#freq").hide();
		$("#filterclean").hide();
	}
})


//update
var rtId;
$(document).on("click",".click_me", function() {
	rtId = $(this).parent().attr("rt_id");
	cleanValue();
//	$(this).attr("data-toggle","modal");
//	$(this).attr("data-target","#rtModal");
	$("#rtSave").attr("mark","update");
	$("#modal-title").html("修改设备信息");
	$(document).find('#rtModal').modal('toggle');
	$.ajax({
		url : 'repertory_fetch',
		type : 'post',
		dataType : 'json',
		data : {"rtId" : rtId,},// {"后台",""}
		success : fetchCallback
	});
})
function fetchCallback(data) {
	if(data.status == "0") {
		alert("error");
		return;
	}
	else if(data.status == "1") {
		var temp = data.rtSearch_list[0];
		$(document).find("#rtDevice").val(temp.rtDevice);
		if(temp.rtDevice == "主要设备") {
			$(document).find("#rtType1").val(temp.rtType);
			$("#rtType1").show();
			$("#rtType2").hide();
			if(temp.rtType == "投影机") {
				$("#filterclean").show();
				$(document).find("#rtFilterCleanPeriod").val(temp.rtFilterCleanPeriod);
				$("#freq").hide();
			}
			else if(temp.rtType == "麦克") {
				$("#filterclean").hide();
				$("#freq").show();
				$(document).find("#rtFreqPoint").val(temp.rtFreqPoint);
			}
			else {
				$("#freq").hide();
				$("#filterclean").hide();
			}
		}
		else if(temp.rtDevice == "耗材设备") {
			$(document).find("#rtType2").val(temp.rtType);
			$("#rtType1").hide();
			$("#rtType2").show();
		}
		$(document).find("#rtNumber").val(temp.rtNumber);
		$(document).find("#rtVersion").val(temp.rtVersion);
		$(document).find("#rtProdDate").val(temp.rtProdDateString);
		$(document).find("#rtApprDate").val(temp.rtApprDateString);
		$(document).find("#rtFactorynum").val(temp.rtFactorynum);
		$(document).find("#rtDeviceStatus").val(temp.rtDeviceStatus);
		$(document).find("#rtReplacePeriod").val(temp.rtReplacePeriod);
	}
	
}
//insert update
$(document).on("click", "#rtSave", function() {
	
	var d_type = $("#rtDevice").val();
	var d_name;
	if (d_type == "") {
		alert("输入不能为空！");
		return;
	} 
	else if(d_type == "主要设备") {
		d_name = $("#rtType1").val();				
	}
	else{
		d_name = $("#rtType2").val();
	}
	if(d_name == "") {
		alert("输入不能为空！");
		return;
	}
	if($("#rtDeviceStatus").val() == "") {
		alert("输入不能为空！");
		return;
	}
	var params = $("#repertory_form").serialize();
	//alert(decodeURIComponent(params,true));
	var fd = new FormData();
	var cnt = $("#repertory_form");
 	fd.append("rtDevice", $(cnt).find("#rtDevice").val());
 	fd.append("rtType",d_name);
 	fd.append("rtNumber", $(cnt).find("[name=rtNumber]").val());
 	fd.append("rtVersion", $(cnt).find("[name=rtVersion]").val());
 	fd.append("rtProdDate", $(cnt).find("[name=rtProdDate]").val());
 	fd.append("rtApprDate", $(cnt).find("[name=rtApprDate]").val());
 	fd.append("rtFactorynum", $(cnt).find("[name=rtFactorynum]").val());
 	fd.append("rtDeviceStatus", $(cnt).find("[name=rtDeviceStatus]").val());
 	fd.append("rtReplacePeriod", $(cnt).find("[name=rtReplacePeriod]").val());
 	fd.append("rtFilterCleanPeriod", $(cnt).find("[name=rtFilterCleanPeriod]").val());
 	fd.append("rtFreqPoint", $(cnt).find("[name=rtFreqPoint]").val());
	
	if($(this).attr("mark") == "insert")
	{
	    $.ajax({  
	        url:'/admin/repertory_insert' ,  
	        type: "POST",  
	        data: fd,  
	        async: true,  
	        cache: false,  
	        contentType: false,  
	        processData: false,  
	        success: repertoryCallback,

	   });  
	}
	else if($(this).attr("mark") == "update") {
		fd.append("rtId", rtId);
		$.ajax({  
	        url:'/admin/repertory_update' ,  
	        type: "POST",  
	        data: fd,  
	        async: true,  
	        cache: false,  
	        contentType: false,  
	        processData: false,  
	        success: updateCallback,

	   });  
		
	}

})

function repertoryCallback(data) {
	if (data.status == "1") {
		$("#repertory_table tr:first").after(data.add_repertory_html);
		var cnt = $(document).find("#repertory_table tr:eq(1)");
		$(cnt).children().eq(0).text(data.rtType);
		$(cnt).children().eq(1).text(data.rtNumber);
		$(cnt).children().eq(2).text(data.rtVersion);
		$(cnt).children().eq(3).text(data.rtProdDateString);
		//$(cnt).children().eq(3).text(data.rtProdDate.substring(0,10));
		$(cnt).children().eq(4).text(data.rtApprDateString);
		$(cnt).children().eq(5).text(data.rtFactorynum);
		$(cnt).children().eq(6).text(data.rtDeviceStatus);
		$(cnt).children().eq(7).text(data.rtReplacePeriod + "/小时");
		$(cnt).attr("rt_id", data.rtId);
		$('#rtModal').modal('hide');
		alert("保存成功！ ");

	}
}

function updateCallback(data) {
	if(data.status == "1") {
		var line = $(document).find("#repertory_table tr[rt_id = " + data.rtId +"]");
		$(line).children().eq(0).text(data.rtType);
		$(line).children().eq(1).text(data.rtNumber);
		$(line).children().eq(2).text(data.rtVersion);
		$(line).children().eq(3).text(data.rtProdDateString);
		$(line).children().eq(4).text(data.rtApprDateString);
		$(line).children().eq(5).text(data.rtFactorynum);
		$(line).children().eq(6).text(data.rtDeviceStatus);
		$(line).children().eq(7).text(data.rtReplacePeriod + "/小时");
		$('#rtModal').modal('hide');
		alert("修改成功！ ");
	}
}


//delete
var delete_rtId;
$(document).on("click", ".delete", function() {
	var temp = confirm("删除不可恢复！");
	if (temp == true) {
		delete_rtId = $(this).parents("tr").attr("rt_id");// attr所选元素属性值
		$.ajax({
			url : 'repertory_delete',
			type : 'post',
			dataType : 'json',
			data : {"rtId" : delete_rtId,},// {"后台",""}
			success : deleteCallback
		});
	}
})

function deleteCallback(data) {
	if (data.status == "0") {
		alert("删除数据不存在！ ");
	} else if (data.status == "1") {
		$(document).find("tr[rt_id=" + delete_rtId + "]").remove();
	}
}

//search
$(document).find("#sDevice").change(function() {
	var selectvalue = $("#sDevice option:selected").attr("value");
	if (selectvalue == "") {
		$("#main").hide();
		$("#cost").hide();
		selectDevice();
	} else if (selectvalue == "主要设备") {
		$("#main").show();
		$("#cost").hide();
		$(document).find("#sMainDevice option:first").attr("selected","selected");
		selectDevice();
	} else if(selectvalue == "耗材设备") {
		$("#main").hide();
		$("#cost").show();	
		$(document).find("#sCostDevice option:first").attr("selected","selected");
		selectDevice();
	}
	
})
				   
$(document).find("#sMainDevice").change(function() {
	selectDevice();
})
$(document).find("#sCostDevice").change(function() {
	selectDevice();
})
$(document).find("#sDeviceStatus").change(function() {
	selectDevice();
})

function selectDevice() {
	var keyword = $("#repertory_search").serialize();
	//alert(decodeURIComponent(keyword,true));
	$.ajax({
		url : 'repertory_search',
		type : 'post',
		dataType : 'json',
		data : keyword,
		success : searchCallback
	});
}

function searchCallback(data) {
	if (data.status == "1") {
//		$("#repertory_table tr:not(:first)").remove();
		$(document).find("#noResult").text("");
		$(document).find("#rtSearchLen").text(data.repertory_list.length);
		$(document).find("#repertoryTableDiv").html(data.repertory_table);

	} else if (data.status == "0") {
		$(document).find("#rtSearchLen").text(0);
		$(document).find("#repertory_table tr:not(:first)").remove();
		$(document).find("#noResult").text("无查询结果");
	}
}


//import excel
$(document).on("click","#rtUpload",function() {
	var params = new FormData();
	params.append("file", document.getElementById("excelFile").files[0]);
	$.ajax({
		url: '/admin/repertory_importExcel',
		type: "POST",  
        data: params,  
        async: true,  
        cache: false,  
        contentType: false,  
        processData: false,  
        success: importCallback,
	});
	
})

function importCallback(data) {
	
	if(data.status == "1") 
	{
		alert("导入成功！");
		window.location.reload();
	}
	else if(data.status == "0")
	{
		alert("导入失败！可能文件格式有误！");
	}
	else if(data.status == "2")
	{
		alert("导入数据有误！");
	}
}

