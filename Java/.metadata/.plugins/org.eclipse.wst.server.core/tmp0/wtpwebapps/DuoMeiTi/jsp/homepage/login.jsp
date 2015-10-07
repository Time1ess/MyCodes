<%@ include file="/jsp/base/taglib.jsp" %>





<layout:override name="main_content">
<br/>

	<form action="" method="POST" style="position:relative;left:20%">
	
	  <div class="form-group">
	    <label for="username">用户名</label>	    
	    <input style="width:30%" type="text" class="form-control" name="username" value="<s:property value="username"/>" placeholder="">
	  </div>	  
	  
	  <div class="form-group">
	    <label for="password">密码</label>
	    <input style="width:30%" type="password" class="form-control" name="password" value="<s:property value="password"/>" placeholder="">
	  </div>
	  
	  

<!-- 	  <div class="form-group"> -->

<!-- 			<label class="radio-inline"> -->
<%-- 			  <input type="radio" name="role" value="<s:property value="AdminRole"/>" checked> 系统管理员 --%>
<!-- 			</label> -->
			
<!-- 			<label class="radio-inline"> -->
<%-- 			  <input type="radio" name="role" value="<s:property value="StudentRole"/>" > 在职学生 --%>
<!-- 			</label> -->
<!-- 			<label class="radio-inline"> -->
<%-- 			  <input type="radio" name="role" value="<s:property value="TeacherRole"/>" > 授课教师 --%>
			  
<!-- 			</label> -->

				  	
<!-- 	  </div> -->
	  
	  <button type="submit" class="btn btn-default" id="login">登录</button>
	</form>
	
	
	<script>
	
// 		$(document).on("click", "#login", function() {
			
// 			alert($("form").serialize());
// 			var role = "NoRole";
// 			if(document.getElementById("AdminRole").checked) 
// 				role = "AdminRole";
// 			else if(document.getElementById("StudentRole").checked) 
// 				role = "StudentRole";
// 			else if(document.getElementById("AdminRole").checked) 
// 				role = "TeacherRole";
			
			


			
// 		})
		
	</script>
	



</layout:override>



<%@ include file="/jsp/homepage/new_home_base.jsp" %>

