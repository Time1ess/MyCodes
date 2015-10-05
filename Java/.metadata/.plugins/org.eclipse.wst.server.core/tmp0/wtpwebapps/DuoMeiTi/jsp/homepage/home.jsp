<%@ include file="/jsp/base/taglib.jsp" %>





<layout:override name="main_content">

<!-- 	<br/><br/> -->
<!-- 	<a href="/login" class="btn btn-primary">跳到登录</a> -->
	
<!-- 	<br/><br/> -->
<!-- 	<a href="/login_success" class="btn btn-default">跳到登录成功界面，可以在这个界面可以退出登录</a> -->
	
	
	<br/><br/>
	<a href="/register" class="btn btn-default">跳到注册</a>
<!-- 	<br/><br/> -->
<!-- 	<a href="/student_register" class="btn btn-default">跳到学生注册</a> -->
<!-- 	<br/><br/> -->
<!-- 	<a href="/admin/" class="btn btn-default">跳到系统管理员</a> -->
	
	<br/><br/>
	<a href="/file_upload" class="btn btn-success">跳到文件上传示例</a>
	
	
	<br/><br/>
	<a href="/admin_eg" class="btn btn-default">跳到系统管理员带上边框的形式</a>

<!-- 	<br/><br/> -->
<!-- 	<a href="/admin_register" class="btn btn-default">跳到系统管理员注册</a> -->
	<br/><br/>
	
	
	
	
<nav class="navbar navbar-default">
  <div class="container-fluid">
  
  
  
    <!-- Brand and toggle get grouped for better mobile display -->
    <div class="navbar-header">
<!--       <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1" aria-expanded="false"> -->
<!--         <span class="sr-only">Toggle navigation</span> -->
<!--         <span class="icon-bar"></span> -->
<!--         <span class="icon-bar"></span> -->
<!--         <span class="icon-bar"></span> -->
<!--       </button> -->
      <a class="navbar-brand" href="/">主页</a>
    </div>

<!--     Collect the nav links, forms, and other content for toggling -->
    <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
      <ul class="nav navbar-nav">
      
      

      </ul>
      
      



      <ul class="nav navbar-nav navbar-right">
      
      
        <li><a href="/login">登录</a></li>
        <li class="dropdown">
			<a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">注册 <span class="caret"></span></a>
			<ul class="dropdown-menu">
			  <li><a href="/admin_register">系统管理员注册</a></li>
			  <li role="separator" class="divider"></li>
			  <li><a href="/student_register">在职学生注册</a></li>
			  <li role="separator" class="divider"></li>
			  <li><a href="/teacher_register">授课教师注册</a></li>

			</ul>
       	</li>

        

      </ul>
              
      
      
      
      
    </div>
    
    
    
    
    
    
    
  </div><!-- /.container-fluid -->
</nav>
	
	
	

	
	<br/>
	
	

    <table class="jumbotron container table table-bordered" id="user_table">
	
		<tr class="active">
			<th> 文件列表 </th>
		</tr>
		
		
		<s:iterator value="file_path_list" var="i" status="index" >  
			<tr class="success" >
				<td>   
					<a href="<s:property value="#i.filePath"/> "> 
						
						<s:property value="#i.filePath.split('/')[#i.filePath.split('/').length - 1]"/>
						<s:property value="#i.filePath."/>

					</a>   
				</td>

			</tr>
		</s:iterator> 	

	</table>
	

<div class="row" style="height:300px">
  <div class="col-md-5 well" style="height:400px;margin:10px">.col-md-6sdfsf</div>
  
  <div class="col-md-offset-1 col-md-5 well" style="height:400px;margin:10px">.col-md-6</div>
</div>
  
  
  
  
  
  
  
  
	
	
	

	
	
	
	
	
	
	
	
	
	
<!--   </div> -->
<!-- </div>	 -->
	
	
	
	
	

<!-- <form class="form-inline"> -->
<!--   <div class="form-group" id="one"> -->
<!--     one -->
<!--   </div> -->
<!--   <div class="form-group" id ="two"> -->
<!--     two -->
<!--   </div>     -->
<!-- </form> -->

<!-- <button id="con" class="btn btn-primary"> doubi -->
<!-- </button> -->

<!-- <script> -->

<!-- // $(document).find("#one").hide(); -->
<!-- // $(document).find("#two").hide(); -->
<!-- // var cnt = 0; -->
<!-- // $(document).on("click", "#con", function(){ -->
<!-- // 	cnt ++; -->
<!-- // 	$(document).find("#one").hide(); -->
<!-- // 	$(document).find("#two").hide(); -->
<!-- // 	if(cnt % 2 == 1) $(document).find("#one").show(); -->
<!-- // 	else $(document).find("#two").show(); -->
	
	
<!-- // }) -->
	


<!-- </script> -->

	
	
	
	

</layout:override>














<%@ include file="/jsp/homepage/base.jsp" %>


