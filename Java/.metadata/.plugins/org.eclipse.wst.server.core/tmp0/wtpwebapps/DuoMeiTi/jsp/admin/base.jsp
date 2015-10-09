<%@ include file="/jsp/base/taglib.jsp" %>



<layout:override name="menu_list">

	<div class="menu-list">
	    <a href="/admin/classroom/" class="menu-button-middle"><span class="glyphicon glyphicon-blackboard">&nbsp;教室管理</span></a>
	    <a href="/admin/repertory" class="menu-button-middle"><span class="glyphicon glyphicon-th-large">&nbsp;设备管理</span></a>
	    <a href="/admin/classroomDevice/maintainRecords" class="menu-button-middle"><span class="glyphicon glyphicon-th">&nbsp;维修记录管理</span></a>
	    <a href="/admin/student_manage/" class="menu-button-middle"><span class="glyphicon glyphicon-list-alt">&nbsp;在职学生管理</span></a>
	    <a href="/admin/user_request/" class="menu-button-middle"><span class="glyphicon glyphicon-list-alt">&nbsp;用户注册请求</span></a>
	    
	    <a href="/admin/usefdsaf" class="menu-button-middle"><span class="glyphicon glyphicon-list-alt">&nbsp;账号生成</span></a>

<!-- 	    <a href="/admin/wer" class="menu-button-middle"><span class="glyphicon glyphicon-list-alt">&nbsp;主页修改</span></a> -->
<!-- 	    <a href="/admin/notice" class="menu-button-middle"><span class="glyphicon glyphicon-list-alt">&nbsp;公告管理</span></a> -->

	    <a href="/admin/HomepageModify/" class="menu-button-middle"><span class="glyphicon glyphicon-list-alt">&nbsp;主页修改</span></a>
	    <a href="/admin/adf" class="menu-button-middle"><span class="glyphicon glyphicon-list-alt">&nbsp;日志管理</span></a>
	    <a href="/admin/asdf" class="menu-button-middle"><span class="glyphicon glyphicon-list-alt">&nbsp;远程控制</span></a>
	    <a href="/admin/modifypassword" class="menu-button-middle"><span class="glyphicon glyphicon-lock">&nbsp;修改密码</span></a>
	    <a href="/admin/user_information" class="menu-button-middle"><span class="glyphicon glyphicon-list-alt">&nbsp;个人信息</span></a>
	    <a href="/logout" class="menu-button-middle"><span class="glyphicon glyphicon-list-alt">&nbsp;安全退出</span></a>
	    <div class="menu-blank"></div>
	</div>
	
	 
 </layout:override>








<%@ include file="/jsp/base/user_base.jsp" %>
