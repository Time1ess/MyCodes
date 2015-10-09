<%@ include file="/jsp/base/taglib.jsp" %>


<layout:override name="mycontent">

	<div class="mycontent">
		<div id="classlist-content">
			<table class="classlist table table-bordered table-striped" id="classlist">
				<tr class="row">
					<th>姓名</th>
					<th>性别</th>
					<th>学号</th>
					<th>身份证号</th>
					<th>银行卡号</th>
					<th>院系信息</th>
					<th>联系方式</th>
					<th>审核状态</th>
					<th>修改</th>
				</tr>
				
		<s:iterator value="student_list" var="i" status="index">
			<s:if test="%{#i.isPassed>0}">		
				<tr class="row" id=<s:property value="#i.id"/> > 
					<td><s:property value="#i.user.fullName"/></td>
					<td><s:property value="#i.user.sex"/></td>
					<td><s:property value="#i.studentId"/></td>
					<td><s:property value="#i.idCard"/></td>
					<td><s:property value="#i.bankCard"/></td>
					<td><s:property value="#i.college"/></td>
					<td><s:property value="#i.user.phoneNumber"/></td>
				<s:if test="%{#i.isPassed==1}">
					<td>审核不通过</td>
				</s:if>
				<s:else >
					<td>审核通过</td>
				</s:else>
					<td>
						<button type="button" class="btn btn-primary btn-sm change">撤销</button>
					</td>	
				</tr>
			</s:if>
		</s:iterator>
			</table>
		</div>
	</div>
	
	<script>
	$(".change").click(function(){
		var id=$(this).closest("tr").attr("id");
		/* var isPass=$('#judge').find("option:selected").val(); */
		$.ajax({
			url: 'request_change',
	        type: 'post',
	        dataType: 'json',
	        data:{userid:id},
	        success:changeCallBack
		});
	})
	
	function changeCallBack(data){
		if(data.strValue=="success"){
			var p=$("#"+data.userid);
			$("#"+data.userid).remove();
		}
		else alert("something wrong!!");
	}
	</script>
	
	

</layout:override>







<%@ include file="/jsp/admin/users_request.jsp" %>