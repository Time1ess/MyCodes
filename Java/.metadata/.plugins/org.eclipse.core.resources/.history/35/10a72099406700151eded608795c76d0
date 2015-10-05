<%@ include file="/jsp/base/taglib.jsp" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<layout:override name="main_content">
	<link href="/css/admin/classroom_detail.css" rel="stylesheet" />
	<script type='text/javascript' src="/js/admin/classroom_detail.js"></script>
	<script type="text/javascript">
	window.onload = function () {
	    $('.form_date').datetimepicker({
	        language:  'zh-CN',
	        weekStart: 1,
	        todayBtn:  1,
			autoclose: 1,
			todayHighlight: 1,
			startView: 2,
			minView: 2,
			forceParse: 0
	    });
	}
	</script>
	<div class="mycontent">
		<div class="row">
			<div class="col-lg-6 col-lg-offset-3 classbuilding">
				<span><s:property value="build_name"/>&nbsp;&nbsp;<s:property value="classroom.classroom_num"/></span>&nbsp;&nbsp;&nbsp;&nbsp;
				<span>负责人:</span>
				<span id="classroomid" style="visibility:hidden"><s:property value="classroom.id"/></span>
				<span class="director-span"><s:property value="classroom.principal.user.username"/></span>
			</div>
			</div>
		<hr>
	
		<!-- Modal -->
		<div class="modal fade" id="schedule-modal" tabindex="-1" role="dialog"
			aria-labelledby="myModalLabel">
			<div class="modal-dialog" role="document">
				<div class="modal-content">
					<div class="modal-header">
						<button type="button" class="close" data-dismiss="modal"
							aria-label="Close">
							<span aria-hidden="true">&times;</span>
						</button>
						<h4 class="modal-title">课表</h4>
					</div>
					<div class="modal-body">
						<div class="form-group">
							<label for="dtp_input2" class="col-md-2 control-label">选择日期</label>
							<div style="float:left;position:relative;" class="input-group date form_date col-md-5" data-date="" data-date-format="dd MM yyyy" data-link-field="dtp_input2" data-link-format="yyyy-mm-dd">
								<input class="form-control" size="16" type="text" value="" readonly> 
								<span class="input-group-addon">
									<span class="glyphicon glyphicon-remove"></span>
								</span>
								<span class="input-group-addon">
									<span class="glyphicon glyphicon-calendar"></span>
								</span>
							</div>
							<input type="hidden" id="dtp_input2" value="" />
							<button type="button" style="float:right" class="btn btn-primary">查询</button>
							<br /><br /><br />
						</div>
						<table class="table table-bordered">
							<thead>
								<tr><td>1-2节</td><td>3-4节</td><td>5-6节</td><td>7-8节</td><td>9-10节</td></tr>
							</thead>
							<tbody>
								<tr><td>C语言</td><td>Java语言</td><td>PHP语言</td><td>C#语言</td><td>C++语言</td></tr>
							</tbody>
						</table>
					</div>
					<div class="modal-footer">
						<button type="button" class="btn btn-default" data-dismiss="modal">关闭</button>
					</div>
				</div>
			</div>
		</div>
		<div class="modal fade" id="check-record-modal" tabindex="-1" role="dialog"
			aria-labelledby="myModalLabel">
			<div class="modal-dialog" role="document">
				<div class="modal-content">
					<div class="modal-header">
						<button type="button" class="close" data-dismiss="modal"
							aria-label="Close">
							<span aria-hidden="true">&times;</span>
						</button>
						<h4 class="modal-title">填写周检查记录</h4>
					</div>
					<div class="modal-body">
						<textarea class="form-control" rows="3" id="checkdetail"></textarea>
					</div>
					<div class="modal-footer">
						<button type="button" class="btn btn-primary" onclick="checkrecord_submit()">提交</button>
						<button type="button" class="btn btn-default" data-dismiss="modal">取消</button>
					</div>
				</div>
			</div>
		</div>
		<div class="modal fade" id="repair-record-modal" tabindex="-1" role="dialog"
			aria-labelledby="myModalLabel">
			<div class="modal-dialog" role="document">
				<div class="modal-content">
					<div class="modal-header">
						<button type="button" class="close" data-dismiss="modal"
							aria-label="Close">
							<span aria-hidden="true">&times;</span>
						</button>
						<h4 class="modal-title">填写维修记录</h4>
					</div>
					<div class="modal-body">
						<div>设备：<span class="control-label" id="selectType"></span>&nbsp;&nbsp;&nbsp;&nbsp;资产编号：<span class="control-label" id="selectNum"></span></div>
						<textarea class="form-control" rows="3" id="repairdetail"></textarea>
					</div>
					<div class="modal-footer">
						<button type="button" class="btn btn-primary" onclick="repairrecord_submit()">提交</button>
						<button type="button" class="btn btn-default" data-dismiss="modal">取消</button>
					</div>
				</div>
			</div>
		</div>

		<div class="container-fluid">
			<div class="row col-lg-12">
				<div class="col-lg-7">
				<!-- <form action="#" method="post" id="addclassroomdevice"> -->
					<p style="float:left;vertical-align:bottom;">添加设备:</p>
					<input type="text" class="form-control" id="zichanhao" style="width:30%;float:left;margin-left:5%;" placeholder="请输入资产编号">
					<!-- <button type="submit" class="btn btn-info btn-sm" style="margin-left:5%">查询</button> -->
					<button type="button" class="btn btn-primary btn-sm" style="margin-left:5%" onclick="add_classroomrt(<s:property value="#session.ret"/>)">添加</button>
				<!-- </form> -->
				<script>
					function add_classroomrt() {
						var classroomid = $("#classroomid").text();
						var bh = $("#zichanhao").val();
						var href="<%=path%>/admin/classroomDevice/add_action";
						
						$.ajax({
							url : href,
							type : 'post',
							dataType : 'json',
							data : {
								"id" : classroomid,
								"bh" : bh
							}, 
							success : addcallback
						});
					}
					
					function addcallback(data) {
						if (parseInt(data.ret))
							alert("Ok，添加成功");
						else
							alert("Sorry，添加失败");
					}
				</script>
				</div>
				<div class="col-lg-2">
					<button type="button" class="btn btn-primary btn-sm" data-toggle="modal" data-target="#schedule-modal">查看课表</button>
					</div>
				<div class="col-lg-2">
					<button type="button" class="btn btn-primary btn-sm" data-toggle="modal" data-target="#check-record-modal">填写周检查记录</button>
				</div>
			</div>
		</div>
		<div class="detail-div">
			<div class="device">
				<ul>
					<s:iterator value="classroom.repertorys" var="device" status="i">
						<li id="device-<s:property value="#i.index"/>" />
							<div style="margin-bottom:5px">
								<label class="control-label device-type-label"><s:property value="#device.rtType"/>&nbsp;</label>
								<span>
									<button type="button" class="btn btn-primary btn-sm"  
									onclick="openRepairMoadl(<s:property value="#i.index"/>)">维修</button>
								</span>
								<span style="visibility:hidden" class="device-id-span"><s:property value="#device.rtId"/></span>
								<span style="visibility:hidden" class="device-num-span"><s:property value="#device.rtNumber"/></span>
							</div>
							<table class="table device-table-bordered">
								<thead>
									<tr><td>资产编号</td><td>型号</td><td>名称</td><td>出厂号</td><td>出厂日期</td><td>审批日期</td></tr>
								</thead>
								<tbody>
									<tr><td><s:property value="#device.rtNumber"/></td>
										<td><s:property value="#device.rtVersion"/></td>
										<td><s:property value="#device.rtType"/></td>
										<td><s:property value="#device.rtFactorynum"/></td>
										<td><s:property value="#device.rtProdDate"/></td>
										<td><s:property value="#device.rtApprDate"/></td>
									</tr>
								</tbody>
							</table>
						</li>
					</s:iterator>
				</ul>
			</div>
			<div class="record">
				<ul>
					<li>
						<label class="control-label">周检查记录：</label>
						<table class="table device-table-bordered" id="checkrecord_table">
							<thead>
								<tr><td>检查人</td><td>教室状况</td><td>检查时间</td></tr>
							</thead>
							<tbody>
								<s:iterator value="checkrecords" var="checkrecord" status="i">
									<tr>
										<td width="20%"><s:property value="#checkrecord.user.fullName"/></td>
										<td><s:property value="#checkrecord.checkdetail"/></td>
										<td><s:property value="#checkrecord.checkdate"/></td>
									</tr>
								</s:iterator>
							</tbody>
						</table>
					</li>
					<li>
					<label class="control-label">维修记录：</label>
						<table class="table device-table-bordered" id="repairrecord_table">
							<thead>
								<tr><td>维修人</td><td>维修设备</td><td>维修情况</td><td>维修时间</td></tr>
							</thead>
							<tbody>
								<s:iterator value="repairrecords" var="repairrecord" status="i">
									<tr>
										<td width="20%"><s:property value="#repairrecord.repairman.fullName"/></td>
										<td><s:property value="#repairrecord.device.rtType"/></td>
										<td><s:property value="#repairrecord.repairdetail"/></td>
										<td><s:property value="#repairrecord.repairdate"/></td>
									</tr>
								</s:iterator>
							</tbody>
						</table>
					</li>
				</ul>
			</div>
		</div>
	</div>
	
</layout:override>

<%@ include file="base.jsp" %>