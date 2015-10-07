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
 	<br />
 	<br />
    <%//修改密码前端界面  %>
    <div>
 	<form class="form-inline" id="admin_modify_password" style="margin-left:350px;" action="ModifyPassword" method="POST"  >
 	  		
  	<div class="form-group ">
    		<label >输&nbsp;入&nbsp;原&nbsp;密&nbsp;码&nbsp;</label>
    			<div class="input-group">
      				<span class="input-group-addon"><span class="glyphicon glyphicon-lock"></span></span>
      				<input type="password" class="form-control" id="oldPsw" iid=<s:property value="#session.user_id"/>>   		
    			</div>
    		<br />
    		<br />		
  		    <label >输&nbsp;入&nbsp;新&nbsp;密&nbsp;码&nbsp;</label>
    			<div class="input-group">
      				<span class="input-group-addon"><span class="glyphicon glyphicon-lock"></span></span>
      				<input type="password" class="form-control" id="newPsw" >
    			</div>
    		<br />
    		<br />
    		<label >确&nbsp;认&nbsp;新&nbsp;密&nbsp;码&nbsp;</label>
    			<div class="input-group">
      				<span class="input-group-addon"><span class="glyphicon glyphicon-lock"></span></span>
      				<input type="password" class="form-control" id="rePsw" >
    			</div>
    		<br />
    		<br />
    		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    		<button type="button"  class="btn btn-primary" id="confirm" onclick="psw_change_ensure()">确认</button>
    		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    		<button type="button"  class="btn btn-primary" id="reset" onclick="psw_change_reset()">重置</button>
	    </div>
	     
	</form>
	</div>
	
</div>

<script type="text/javascript" src="/js/admin/modify_password.js"></script>
   
</layout:override>

<%@ include file="/jsp/admin/base.jsp" %>