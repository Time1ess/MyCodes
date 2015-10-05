<%@page import="java.util.ArrayList,model.Classroom"%>
<%@ include file="/jsp/base/taglib.jsp"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<layout:override name="main_content">
<style>
td,tr,th{
	text-align:center;
	vertical-align:middle;
}
</style>

	<div class="mycontent">
		<div class="row">
			<a type="button" class="btn btn-primary"
				style="width: 49%; float: left" href="/admin/classroomDevice/maintainRecords">设备维修记录</a>
			<a type="button" class="btn btn-primary"
				style="width: 49%; float: right" href="/admin/classroomDevice/equipmentQueryAndEdit">设备信息查询及批量修改</a>
		</div>
		<hr>

		<div class="radios">
			<label class="radio-inline" style="margin-left:5%" > <input type="radio"
				name="radio-select" value="0"
				onclick="return showdiv('#personCondition')" checked> 按负责人
			</label> <!-- <label class="radio-inline" style="margin-left:5%" > <input type="radio"
				name="radio-select" value="1"
				onclick="return showdiv('#buildingCondition')"> 按教学楼
			</label>  --><label class="radio-inline" style="margin-left:5%" > <input type="radio"
				name="radio-select" value="2"
				onclick="return showdiv('#equipmentCondition')"> 按设备
			</label> <label class="radio-inline" style="margin-left:5%" > <input type="radio"
				name="radio-select" value="3"
				onclick="return showdiv('#timeCondition')"> 按时间
			</label>
			<a id="commitSearch" <%-- href="<%=path%>/admin/classroomDevice/query_action" --%> type="button" target="myFrame" class="btn btn-default" style="float:right;margin-right:5%" onclick="startSearch()">检索维修记录</a>
			<%-- <a id="commitExport" href="<%=path%>/admin/classroomDevice/query_action" type="button" target="myFrame" class="btn btn-default" style="float:right;margin-right:5%">导出检索记录</a> --%>
		</div>
		<br />
		<div class="searchCondition" id="conditions">
			<div class="searchCondition-person" id="personCondition">
				<select id="principal" class="form-control" style="width: 10%; float: left">
					<option value="0">姓名</option>
					<option value="1">学号</option>
				</select>
				<input type="text" class="form-control" id="personVal" style="width: 30%">
			</div>
			
			<div class="searchCondition-building" id="buildingCondition">
				<select id="building" class="form-control" style="width: 20%; float: left">
					<option value="0">一馆</option>
					<option value="1">综合教学一号楼</option>
				</select>
				<select id="classroom" class="form-control" style="width: 20%">
					<option value="0">101</option>
					<option value="1">205</option>
				</select>
			</div>
			
			<div class="searchCondition-equipment" id="equipmentCondition">
				<select id="deviceid" class="form-control" style="width: 30%">
					<option value="计算机">计算机</option>
					<option value="投影">投影</option>
					<option value="中央控制器">中央控制器</option>
					<option value="外围设备">外围设备</option>
				</select>

			</div>
			
			<div class="searchCondition-time" id="timeCondition">
				<!-- <select id="time" class="form-control" style="width: 30%">
					<option value="0">2015年9月</option>
					<option value="1">2015年8月</option>
					<option value="2">2015年7月</option>
					<option value="3">2015年6月</option>
				</select> -->
				<script type="text/javascript" src="../../js/admin/Calendar3.js"></script>
					<tr>
						<td>
							开始时间：
						</td>
						<td>
							<input type="text" size="20" maxlength="10" id="startTime" style="width: 15%" 
									onclick="new Calendar().show(this);" readonly="readonly">
						</td>
					</tr>
					<tr>
						<td>
							结束时间：
						</td>
						<td>
							<input type="text" size="20" maxlength="10" id="endTime" style="width: 15%" 
								onclick="new Calendar().show(this);" readonly="readonly">
						</td>
					</tr>
			</div>
		</div>
		
		<br />
		<p>
			 <!-- <script language="javascript" type="text/javascript">
				//var items=$(":radio:checked"); //获取选中的项 

				//alert(items.val()); //拿到选中项的值 
			</script> -->
		<p/>
		<%-- <form class="form-horizontal" action="classroom_search"--%>

		<div id="maintainRecords_table">
			<iframe name="myFrame" frameborder="0" scrolling="no" style="width:100%;" height="200px" src="/jsp/admin/record_query.jsp"></iframe>
		</div>
	</div>

	<script language="javascript" type="text/javascript">
		
	</script>




	<script>
	
		function sc_condition(type,val)
		{
			var href="<%=path%>/admin/classroomDevice/query_action";
			href=href+"?Type="+type+"&Value="+val;
			document.getElementById("commitSearch").href=href;
			/* alert(type + ":" +val); */
		}
		function sc_principal() {
			
			var optionval = $("#principal option:selected").val();
			var personval=$("#personVal").val();
			sc_condition(optionval,personval);
		}
		
		function sc_building() {
			/* var options = $("#building option:selected");
			var options1 = $("#classroom option:selected");
			alert("this is 1: " + options.val() + " - " + options1.val()); */
			alert("There's no need!");
		}
		
		function sc_device() {
			var optionval = $("#deviceid option:selected").val();
			sc_condition('2',optionval);
		}
		
		function sc_time() {
			/* var optionval = $("#time option:selected").val() */
			var str = $("#startTime").val();
			var end = $("#endTime").val();
			optionval = str + end;
			sc_condition('3',optionval);
		}
		
		function startSearch() {
			var items=$(":radio:checked"); //获取选中的项;
			switch (parseInt(items.val())) {
				case 0:
					sc_principal();
					break;
				case 1:
					sc_building();
					break;
				case 2:
					
					sc_device();
					break;
				case 3:
					sc_time();
					break;
				default:
					alert("ERROR:Wrong val.");
					return false;
			} 
			return true;
		}
	
		function showdiv(objId) {
			$('#personCondition').hide();
			$('#buildingCondition').hide();
			$('#equipmentCondition').hide();
			$('#timeCondition').hide();
			$(objId).show();
			return true;
		}
		function hidediv(objId) {
			document.getElementById(objId).style.display = "none";
		}
		$(window).load(function() {
			$('#personCondition').show();
			$('#buildingCondition').hide();
			$('#equipmentCondition').hide();
			$('#timeCondition').hide();
		});

		function ClassroomSearchCallback(data) {
			if (data.status == "0") {

				$("#classroom_search_table").html(data.classroominfo.html);
				animatedShow("查询成功");
			} else if (data.status == "1") {
				animatedShow("查询关键字为空");
			} else {
				alert("error with status" + data.status);
			}
			//$("#add_new_courseplan").attr("disabled",false);

			//     	alert($(document).find("#added_user_tr").html());
			//     	alert(data.added_user_html);
			//     	alert(data.username);
		}
	</script>
</layout:override>

<%@ include file="/jsp/admin/base.jsp"%>