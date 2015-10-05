<%@ include file="/jsp/base/taglib.jsp" %>





<layout:override name="main_content">
<br/>

	<form class="form-inline" action="register" method="POST" id="register_form">
	  <div class="form-group">
	    <label for="username">Name</label>	    
	    <input type="text" class="form-control" name="username" value="<s:property value="username"/>" placeholder="">
	  </div>
	  
	  
	  <div class="form-group">
	    <label for="password">Password</label>
	    <input type="password" class="form-control" name="password" value="<s:property value="password"/>" placeholder="">
	  </div>
	  
	  <button type="button" class="btn btn-default register">注册</button>
	</form>	
	<br/>
	
	
	<div class="alert alert-info" role="alert" id="alert_register_info"  style="display:none">
	<br/>
	</div>	
	
	
	
	
	<table class="table table-bordered" id="user_table">
	
		<tr class="active">
			<th> Username </th>
			<th> Password </th>
			<th> 删除</th>
		</tr>
		
		
		<s:iterator value="user_list" var="i" status="index" >  
			<tr class="success" user_id=<s:property value="#i.id"/> >
				<td>   <s:property value="#i.username"/>    </td>
				<td>   <s:property value="#i.password"/>   </td>
				<td> <button type="button" class="btn btn-danger delete">删除</button> 
				 </td>
			</tr>
		</s:iterator>  
		
		
		

	</table>
	
	
	
	
	

<script>
	var deleted_user_id;
	$(document).on("click", ".delete", function (){
		deleted_user_id = $(this).parents("tr").attr("user_id");
// 	    alert(deleted_user_id);
// 	    alert(typeof user_id);

	    $.ajax({
	      url: 'register_delete',
	      type: 'post',
	      dataType: 'json',
	      data: {"user_id": deleted_user_id,},
	      success: deleteCallback
	    });
	
	});
	
	function deleteCallback(data) {
		
		if(data.status == "0")
		{
			animatedShow("删除成功");
			$(document).find("tr[user_id=" + deleted_user_id + "]").remove();
		}
		else if(data.status== "1")
		{
			animatedShow("删除不存在数据");
		}
		else 
		{
			alert("error");
		}
		
		
    }
	
    
    $(document).on("click", ".register", function (){
        var params = $('#register_form').serialize(); //利用jquery将表单序列化

        $.ajax({
          url: 'register_save',
          type: 'post',
          dataType: 'json',
          data: params,
          success: registerCallback
        });

    });
    
    function animatedShow(text)
    {
    	$("#alert_register_info").hide();
		$("#alert_register_info").text(text);
		$("#alert_register_info").show(500);
    }
    function registerCallback(data)
    {    	
    	if(data.status == "0")
    	{    		
        	$("#user_table tr:first").after(data.added_user_html);
        	
        	
        	var cnt = $(document).find("#user_table tr:eq(1)");
        	$(cnt).children().eq(0).text(data.username);
        	$(cnt).children().eq(1).text(data.password);
        	
//         	alert(data.user_id);
        	
			
        	$(cnt).attr("user_id", data.user_id);

    		animatedShow("注册成功");
    	}
    	else if(data.status == "1")
    	{
    		animatedShow("注册用户名或者密码为空");
    	}
    	else if(data.status == "2")
   		{
    		animatedShow("注册用户名重复");
   		}
    	else 
   		{
    		alert("error with status" + data.status);
   		}

		
    }
</script>

</layout:override>










<%@ include file="/jsp/homepage/base.jsp" %>

