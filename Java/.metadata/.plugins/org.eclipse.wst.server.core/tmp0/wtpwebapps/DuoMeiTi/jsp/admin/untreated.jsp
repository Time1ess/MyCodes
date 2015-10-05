<%@ include file="/jsp/base/taglib.jsp" %>


<layout:override name="mycontent">

	<div class="mycontent">
		<div id="classlist-content">
			<table class="classlist table table-bordered table-striped" id="student_messeage">
				<tr class="row">
					<th class="col-lg-1.5">姓名</th>
					<th class="col-lg-0.5">性别</th>
					<th class="col-lg-1.5">学号</th>
					<th class="col-lg-2.5">身份证号</th>
					<th class="col-lg-2.5">院系信息</th>
					<th class="col-lg-1.5">联系方式</th>
					<th class="col-lg-1">待审核</th>
					<th class="col-lg-1"></th>
				</tr>
			
			
		<s:iterator value="student_list" var="i" status="index">
			<s:if test="%{#i.isPassed==0}">
				<tr class="row" id=<s:property value="#i.id"/> >
					<td class="col-lg-1.5"> <s:property value="#i.user.fullName"/> </td>
					<td class="col-lg-0.5"> <s:property value="#i.user.sex"/> </td>
					<td class="col-lg-1.5"> <s:property value="#i.studentId"/> </td>
					<td class="col-lg-2.5"> <s:property value="#i.idCard"/> </td>
					<td class="col-lg-2.5"> <s:property value="#i.college"/> </td>
					<td class="col-lg-1.5"> <s:property value="#i.user.phoneNumber"/> </td>
					<form class="form-inline" action="untreated" method="POST" id="request_form">
					<td class="col-lg-1"> 
					<%-- <s:select list="{'不通过','通过'}" name="strValue"></s:select>  --%>
						<select id="judge" name="strValue">
							<option value="1">不通过</option>
							<option value="2">通过</option>
						</select>
					</td>
					</form>
					<td class="col-lg-1 ">
						<button type="button" class="btn btn-primary btn-sm" id="ensure-button">确定</button>
					</td>
				</tr>
			</s:if>		
		</s:iterator>
			</table>
		</div>
	</div>
	
	<script>
	/*
	$(document).on("click", "button", function (){
		var params=$('#request_form').serialize(); //获取Select选择的Value
		var strValue=$('#judge').find("option:selected").text();
		alert(strValue);  
		$.ajax({
			url: 'request_save',
	        type: 'post',
	        dataType: 'json',
	        data:params,
	        success:judgeCallBack
		});
	});
	
	
	 function judgeCallBack(data){
		if(data.status=="0"){
			alert("不通过");
		}
		else if(data.status=="1"){
			alert("通过");
		}
	}
	 */
	 
	$("#ensure-button").click(function(){
		var id=$(this).closest("tr").attr("id");
		var isPass=$('#judge').find("option:selected").val();
		
		$.ajax({
			url: 'request_ensure',
	        type: 'post',
	        dataType: 'json',
	        data:{userid:id,isPassed:isPass},
	        success:ensureCallBack
		});
	})
	
	function ensureCallBack(data){
		if(data.strValue=="success"){
			var t=$("#"+data.userid);
			$("#"+data.userid).remove();
		}
		else alert("something wrong!!");
	}
	</script>
	
	
    

</layout:override>







<%@ include file="/jsp/admin/users_request.jsp" %>