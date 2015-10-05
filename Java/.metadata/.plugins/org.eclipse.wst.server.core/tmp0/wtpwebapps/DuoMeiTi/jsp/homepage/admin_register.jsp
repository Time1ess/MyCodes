<%@ include file="/jsp/base/taglib.jsp"%>

<layout:override name="main_content">
	<br />

	<form class="form-inline" action="student_register" method="POST"
		id="admin_register_form">

		<div class="form-group col-lg-offset-4">
			<label for="username">用&nbsp;&nbsp;户&nbsp;&nbsp;名</label> <input type="text"
				class="form-control" name="username" id="usernameId"
				onblur=checkUsername() value="<s:property value="username"/>"
				placeholder="用作登录的用户名">
		</div>

		<div class="form-group">
			<span style="color: red" id=username_msg>*</span>
		</div>
		  <br><br>
		  
		<div class="form-group col-lg-offset-4">
			<label for="password">密&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;码</label>
			<input type="password" class="form-control" name="password"
				onblur=checkPassword() id="passwordId"
				value="<s:property value="password"/>" placeholder="">
		</div>
		
		<div class="form-group">
			<span style="color: red" id=password_msg>*</span>
		</div>
  <br><br>

		
		<div class="form-group col-lg-offset-4">
			<label for="passwordAgain">确认密码</label> <input type="password"
				class="form-control" name="passwordAgain" id="passwordAgainId"
				onblur=checkPasswordAgain() value="<s:property value="passwordAgain"/>"
				placeholder="">
		</div>
		<div class="form-group">
			<span style="color: red" id=passwordAgain_msg>*</span>
		</div>
		  <br><br>
		<div class="form-group col-lg-offset-4">
			<label for="fullName">姓&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;名</label>
			<input type="text" class="form-control" name="fullName"
				value="<s:property value="fullName"/>" placeholder="">
		</div>
		<br> <br> 


		<%-- <div class="form-group col-lg-offset-1">
			<label for="sex">性&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;别</label>
			<input type="text" class="form-control" name="sexSelect"
				value="<s:property value="unitInfo"/>" placeholder="">
		</div> --%>
		
		<div class="form-group col-lg-offset-4">
	  	<label for="sex">性&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;别</label>
	  	<s:select list="sexSelect"  class="form-control" name="sex" style="width:180px"></s:select>
	  </div>
  	<br><br>
		<div class="form-group col-lg-offset-4">
			<label for="profilePhotoPath">上传头像</label> <input type="text"
				class="form-control" name="profilePhotoPath"
				value="<s:property value="profilePhotoPath"/>" placeholder="">
		</div>

		<br> <br> 




		<div class="form-group col-lg-offset-4">
			<label for="unitInfo">工作单位</label> <input type="text"
				class="form-control" name="unitInfo"
				value="<s:property value="unitInfo"/>" placeholder="">
		</div>
  <br><br>

		<div class="form-group col-lg-offset-4">
			<label for="phoneNumber">联系方式</label> <input type="text"
				class="form-control" name="phoneNumber"
				value="<s:property value="phoneNumber"/>" placeholder="">
		</div>

		<br> <br> 

		<div class="form-group col-lg-offset-4">
			<label for="remark">备&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;注</label>
			<input type="" text"" class="form-control" name="remark"
				value="<s:property value="remark"/>" placeholder="">
		</div>



		<br /> <br />
		<button type="button" class="btn btn-primary col-lg-offset-5">注册</button>
	</form>

	<br />


	<div class="alert alert-info" role="alert" id="alert_register_info"
		style="display: none">
		<br />
	</div>







	<script>

    $(document).on("click", "button", function (){
        var params = $('#admin_register_form').serialize(); //利用jquery将表单序列化
        $.ajax({
          url: 'admin_register_save',
          type: 'post',
          dataType: 'json',
          data: params,
          success: adminRegisterCallback
        });

    });
    
    function animatedShow(text)
    {
    	//alert(text+"animatedShow");
    	$("#alert_register_info").hide();
		$("#alert_register_info").text(text);
		$("#alert_register_info").show(500);
    }
    function adminRegisterCallback(data)
    {    	
    	//alert(data.register_status);
    	
    	if(data.register_status == "0")
    	{    		
        	/* $("#user_table tr:first").after(data.added_user_html);
        	
        	
        	var cnt = $(document).find("#user_table tr:eq(1)");
        	$(cnt).children().eq(0).text(data.username);
        	$(cnt).children().eq(1).text(data.password);
        	c
//         	alert(data.user_id);
        	
			
        	$(cnt).attr("user_id", data.user_id);
 */
    		alert("yeah");
    	}
    	/* else if(data.register_status == "1")
    	{
    		animatedShow("注册用户名或者密码为空");
    	} */
    	else if(data.register_status == "2")
   		{
    		animatedShow("注册用户名重复");
   		}
    	else 
   		{
    		alert("error with status" + data.status);
   		}

		
    }
    
    //输入验证
    function checkUsername(){
    	var val = $("#usernameId").val(); 
    	 if(val=="")
    		{
    		 $("#username_msg").text("非空");
    		 $("#usernameId").focus();
    		} 
    	 else
    		 $("#username_msg").text("");
    }
    
    function checkPassword(){
    	var val = $("#passwordId").val(); 
   	 if(val=="")
   		{
   		 $("#password_msg").text("非空");
   	     $("#passwordId").focus(); 
   		} 
   	 else
   		$("#password_msg").text("");
    }
    
    function checkPasswordAgain(){
    	var val = $("#passwordId").val(); 
      	var val2 = $("#passwordAgainId").val(); 
           	
      	if(val!=val2)
      		{
      		 $("#passwordAgain_msg").text("密码不一致");
      	     $("#passwordAgainId").focus(); 
      		} 
      	 else
      		 {
      		$("#passwordAgain_msg").text("");
      		 }
    }
</script>

</layout:override>










<%@ include file="/jsp/homepage/new_home_base.jsp"%>

