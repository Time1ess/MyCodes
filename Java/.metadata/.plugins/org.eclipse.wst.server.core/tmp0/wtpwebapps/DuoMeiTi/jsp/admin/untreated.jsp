<%@ include file="/jsp/base/taglib.jsp" %>


<layout:override name="mycontent">

	<div class="mycontent">
		<div id="classlist-content">
			<table class="classlist table table-bordered table-striped" id="student_messeage">
				<tr class="row">
					<th>姓名</th>
					<th>性别</th>
					<th>学号</th>
					<th>身份证号</th>
					<th>银行卡号</th>
					<th>院系信息</th>
					<th>联系方式</th>
					<th>待审核</th>
					<th></th>
				</tr>
			
			
		<s:iterator value="student_list" var="i" status="index">
			<s:if test="%{#i.isPassed==0}">
				<tr class="row" id=<s:property value="#i.id"/> >
					<td> <s:property value="#i.user.fullName"/> </td>
					<td> <s:property value="#i.user.sex"/> </td>
					<td> <s:property value="#i.studentId"/> </td>
					<td> <s:property value="#i.idCard"/> </td>
					<td> <s:property value="#i.bankCard"/></td>
					<td> <s:property value="#i.college"/> </td>
					<td> <s:property value="#i.user.phoneNumber"/> </td>
					<form class="form-inline" action="untreated" method="POST" id="request_form">
					<td> 
					<%-- <s:select list="{'不通过','通过'}" name="strValue"></s:select>  --%>
						<select class="judge" name="strValue">
							<option value="1">不通过</option>
							<option value="2">通过</option>
						</select>
					</td>
					</form>
					<td>
						<button type="button" class="btn btn-primary btn-sm ensure-button">确定</button>
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
	 
	$(".ensure-button").click(function(){
		var id=$(this).closest("tr").attr("id");
		var isPass=$(this).closest("td").prev().children("select").val();
		//var isPass=$('#judge').find("option:selected").val();
		
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