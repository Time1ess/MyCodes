<%@ include file="/jsp/base/taglib.jsp" %>


<layout:override name="mycontent">

	<div class="mycontent">
		<div id="classlist-content">
			<table class="classlist table table-bordered table-striped" id="classlist">
				<tr class="row">
					<th class="col-lg-1.5">姓名</th>
					<th class="col-lg-0.5">性别</th>
					<th class="col-lg-1.5">学号</th>
					<th class="col-lg-2.5">身份证号</th>
					<th class="col-lg-2">院系信息</th>
					<th class="col-lg-2">联系方式</th>
					<th class="col-lg-2">审核状态</th>
				</tr>
				
		<s:iterator value="student_list" var="i" status="index">
			<s:if test="%{#i.isPassed>0}">		
				<tr class="row" id=<s:property value="#i.id"/> > 
					<td class="col-lg-1.5"><s:property value="#i.user.fullName"/></td>
					<td class="col-lg-0.5"><s:property value="#i.user.sex"/></td>
					<td class="col-lg-1.5"><s:property value="#i.studentId"/></td>
					<td class="col-lg-2.5"><s:property value="#i.idCard"/></td>
					<td class="col-lg-2"><s:property value="#i.college"/></td>
					<td class="col-lg-2"><s:property value="#i.user.phoneNumber"/></td>
				<s:if test="%{#i.isPassed==1}">
					<td class="col-lg-2">审核不通过</td>
				</s:if>
				<s:else >
					<td class="col-lg-2">审核通过</td>
				</s:else>	
				</tr>
			</s:if>
		</s:iterator>
			</table>
		</div>
	</div>

</layout:override>







<%@ include file="/jsp/admin/users_request.jsp" %>