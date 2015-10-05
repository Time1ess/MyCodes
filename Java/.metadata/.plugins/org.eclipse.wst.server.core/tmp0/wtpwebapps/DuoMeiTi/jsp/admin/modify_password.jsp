<%@ include file="/jsp/base/taglib.jsp" %>

<layout:override name="main_content">
    <%//加入标题  %>
<div class="mycontent">

	<div class="row">
		<div class="col-lg-6 col-lg-offset-3 classbuilding">
			<span>修改密码</span>
	</div>
 	<br />
 	<br />
    <%//修改密码前端界面  %>
 	<form class="form-inline" id="admin_modify_password" style="margin-left:350px;" action="ModifyPassword" method="POST"  >
 	  		
  	<div class="form-group">
    		<label for="input_initial_password">输&nbsp;入&nbsp;原&nbsp;密&nbsp;码&nbsp;</label>
    			<div class="input-group">
      				<span class="input-group-addon"><span class="glyphicon glyphicon-lock"></span></span>
      				<input type="password" class="form-control" id="oldPsw" >   		
    			</div>
    		<br />
    		<br />		
  		    <label for="input_new_paasword">输&nbsp;入&nbsp;新&nbsp;密&nbsp;码&nbsp;</label>
    			<div class="input-group">
      				<span class="input-group-addon"><span class="glyphicon glyphicon-lock"></span></span>
      				<input type="password" class="form-control" id="newPsw" >
    			</div>
    		<br />
    		<br />
    		<label for="repeat_new_password">确&nbsp;认&nbsp;新&nbsp;密&nbsp;码&nbsp;</label>
    			<div class="input-group">
      				<span class="input-group-addon"><span class="glyphicon glyphicon-lock"></span></span>
      				<input type="password" class="form-control" id="rePsw" >
    			</div>
    		<br />
    		<br />
    		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    		<button type="submit"  class="btn btn-primary" id="confirm" onclick="psw_change_ensure()">确认</button>
    		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    		<button type="button"  class="btn btn-primary" id="reset" onclick="psw_change_reset()">重置</button>
	    </div>
	     
	</form>
	
	
</div>

<script type="text/javascript" src="/js/admin/modify_password.js"></script>

<%//在前端验证密码输入的一些规定  %>
<script type="text/javascript">
    function psw_change_ensure()
    {
    	if($("#newPsw").val()!=$("#rePsw").val())
    	{
    		alert("两次密码输入不一致，请重新输入！")
    		return false;
    	}
    	
    	if($("#newPsw").val()=="")
    	{
    		alert("新密码必须非空")
    		return false;
    	}
    	
    }

 <%//重置三个密码输入框 %>   
    function psw_change_reset()
    {
    	$("#oldPsw").val("");
    	$("#newPsw").val("");
    	$("#rePsw").val("");
    	
    }   
</script> 
    
</layout:override>

<%@ include file="/jsp/admin/base.jsp" %>