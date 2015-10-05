<%@ include file="/jsp/base/taglib.jsp" %>





<layout:override name="main_content">
<br/>
<form class="form-inline" action="student_register" method="POST" id="student_register_form">
	  <div class="form-group col-lg-offset-4">
	  	<label for="username">用&nbsp;&nbsp;户&nbsp;&nbsp;名</label>
	  	<input type="text" class="form-control" name="username" id="username" onblur=checkUsername() value="<s:property value="username"/>" placeholder="用作登录的用户名">	
	  </div>
	  <div class="form-group">
	  	<span style="color:red" id="username_msg">*</span>
	  </div>
	  
	  <br><br>
	  
	  <div class="form-group col-lg-offset-4">
	  	<label for="password">密&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;码</label>
	  	<input type="password" class="form-control" name="password" id="password" onblur="checkPassword()" value="<s:property value="password"/>" placeholder="">
	  </div>
	  <div class="form-group">
	  	<span style="color:red" id="password_msg">*</span>
	  </div>
	  
	  <br><br>
	  
	  <div class="form-group col-lg-offset-4">
	  	<label for="passwordAgain">确认密码</label>
	  	<input type="password" class="form-control" id="passwordAgain" name="passwordAgain" onblur="confirmPassword()" value="<s:property value="passwordAgain"/>" placeholder="">
	  </div>
	  <div class="form-group">
	  	<span style="color:red" id="confirm_msg">*</span>
	  </div>
	  
	  <br><br>
	  
	  <div class="form-group col-lg-offset-4">
	  	<label for="fullName">姓&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;名</label>
	  	<input type="text" class="form-control" name="fullName" id="fullName" onblur="checkFullName()" value="<s:property value="fullName"/>" placeholder="您的真实姓名">	
	  </div>
	  <div class="form-group">
	  	<span style="color:red" id="fullName_msg">*</span>
	  </div>
	  
	  <br><br>
	  
	  <div class="form-group col-lg-offset-4">
	  	<label for="sex">性&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;别</label>
	  	<s:select list="sexSelect" class="form-control" name="sex" id="sex" onblur="checkSex()"></s:select>
	  </div>
	  <div class="form-group">
	  	<span style="color:red" id="sex_msg">*</span>
	  </div>
	  
	  <br><br>
	  
	  <div class="form-group col-lg-offset-4">
	  	<label for="studentId">学&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;号</label>
	  	<input type="text" class="form-control" name="studentId" id="studentId" onblur="checkStudentId()" value="<s:property value="studentId"/>" placeholder="">
	  </div>
	  <div class="form-group">
	  	<span style="color:red" id="studentId_msg">*</span>
	  </div>
	  
	  <br><br>
	  
	  <div class="form-group col-lg-offset-4">
	  	<label for="college">院系信息</label>
	  	<s:select list="collegeSelect" class="form-control" name="college"></s:select>
	  </div>
	  
	  <br><br>
	   
	  <div class="form-group col-lg-offset-4">
	  	<label for="phoneNumber">联系方式</label>
	  	<input type="text" class="form-control" name="phoneNumber" value="<s:property value="phoneNumber"/>" placeholder="">	
	  </div>
	  
	  <br><br>
	  
	  <div class="form-group col-lg-offset-4">
	  	<label for="bankCard">银行卡号</label>
	  	<input type="text" class="form-control" name="bankCard" value="<s:property value="bankCard"/>" placeholder="">
	  </div>
	  
	  <br><br>
	  
	  <div class="form-group col-lg-offset-4">
	  	<label for="idCard">身&nbsp;&nbsp;份&nbsp;&nbsp;证</label>
	  	<input type="text" class="form-control" name="idCard" id="idCard" value="<s:property value="idCard"/>" placeholder="">
	  </div>
	  <!-- <div class="form-group">
	  	<span style="color:red">*</span>
	  </div> -->
	  
	  <br><br>
	  
	  <div class="form-group col-lg-offset-4 date">
	  	<label for="entryTime">入职时间</label>
	  	<input type="date" class="form-control" name="entryTime" value="<s:property value="entryTime"/>" placeholder="">
	  </div> 
	  <div class="form-group">
	  	<span style="color:red">*</span>
	  </div>
	  
	  <br> <br>
	 
	  <div class="form-group col-lg-offset-5">
	  	<button type="button" class="btn btn-primary">注册</button>
	  </div>
	  <div class="form-group col-lg-offset-1">
	  	<span style="color:red">(*为必填项)</span>
	  </div>
</form>
	
<script>

    $(document).on("click", "button", function (){
        var params = $('#student_register_form').serialize(); //利用jquery将表单序列化
        $.ajax({
          url: 'student_register_save',
          type: 'post',
          dataType: 'json',
          data: params,
          success: studentRegisterCallback
        });

    });
    
    function checkUsername(){
    	var username = $("#username").val(); 
    	 if(username=="")
    		$("#username_msg").text("不能为空"); 
    	 else
    		 $("#username_msg").text("");
    }
    
    function checkFullName(){
    	var fullName=$('#fullName').val();
    	if(fullName=="")
    		$('#fullName_msg').text("不能为空");
    	else
    		$('#fullName_msg').text("");
    }
    
    function checkPassword(){
    	var password=$('#password').val();
    	if(password=="")
    		$('#password_msg').text("不能为空");
    	else
    		$('#password_msg').text("");
    }
    
    function confirmPassword(){
    	var password=$('#password').val();
    	var passwordAgain=$('#passwordAgain').val();
    	if(!(password==passwordAgain))
    		$('#confirm_msg').text("两次密码不一致");
    	else
    		$('#confirm_msg').text("");
    }
    
    function checkStudentId(){
    	var studentId=$('#studentId').val();
    	if(studentId=="")
    		$('#studentId_msg').text("不能为空");
    	else
    		$('#studentId_msg').text("");
    }
    
    function checkSex(){
    	var studentId=$('#sex').val();
    	if(studentId=="")
    		$('#sex_msg').text("不能为空");
    	else
    		$('#sex_msg').text("");
    }
    
    function studentRegisterCallback(data)
    {    	
    	if(data.register_status == "0")
    	{    		
    		alert("注册成功");
    	}
    	else if(data.register_status == "1")
    	{
    		alert("注册用户名或者密码为空");
    	}
    	else if(data.register_status == "2")
   		{
    		alert("注册用户名重复");
   		}
    	else 
   		{
    		alert("error with status" + data.register_status);
   		}

		
    }
</script>

</layout:override>










<%@ include file="/jsp/homepage/new_home_base.jsp" %>

