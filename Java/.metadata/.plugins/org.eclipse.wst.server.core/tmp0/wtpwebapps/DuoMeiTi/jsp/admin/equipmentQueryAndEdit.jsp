<%@page import="java.util.ArrayList,model.Classroom"%>
<%@ include file="/jsp/base/taglib.jsp"%>

<layout:override name="main_content">
<div class="mycontent">
		<div class="row">
			<a type="button" class="btn btn-primary"
				style="width: 49%; float: left" href="/admin/classroomDevice/maintainRecords">设备维修记录</a>
			<a type="button" class="btn btn-primary"
				style="width: 49%; float: right" href="/admin/classroomDevice/equipmentQueryAndEdit">设备信息查询及批量修改</a>
		</div>
		<hr>
		<div class="detailInput">
	<label class="radio-inline" style="float:left;margin-right:2%">设备类型:</label>
	<input type="text" class="form-control" id="equipmentType"
		style="width: 20%" style="float:left">
	<label class="radio-inline" style="float:left;margin-right:2%">资产编号:</label>
	<input type="text" class="form-control" id="equipmentType"
		style="width: 20%" style="float:left">
	<label class="radio-inline" style="float:left;margin-right:2%">型号:</label>
	<input type="text" class="form-control" id="equipmentType"
		style="width: 20%" style="float:left">
	<label class="radio-inline" style="float:left;margin-right:2%">出厂日期:</label>
	<input type="text" class="form-control" id="equipmentType"
		style="width: 20%" style="float:left">
	<label class="radio-inline" style="float:left;margin-right:2%">审批日期:</label>
	<input type="text" class="form-control" id="equipmentType"
		style="width: 20%" style="float:left">
	<label class="radio-inline" style="float:left;margin-right:2%">出厂号:</label>
	<input type="text" class="form-control" id="equipmentType"
		style="width: 20%" style="float:left">
		</div>
	</div>
</layout:override>

<%@ include file="/jsp/admin/base.jsp"%>