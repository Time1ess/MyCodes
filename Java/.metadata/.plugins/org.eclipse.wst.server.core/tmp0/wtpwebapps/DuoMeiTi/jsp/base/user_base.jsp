<%@ include file="/jsp/base/taglib.jsp" %>



<layout:override name="base_content">
	
<a href="/">
    <div id="headerpic" >
        <ul class="nav navbar-right">
            <li id="welcome_word">
            	欢迎您: <span id="login_user_name"><s:property value="#session.username"/></span>
            </li>
        </ul>
    </div>
</a>

<div class="container-fluid main-container">
    <div class="row col-lg-12">
        <div class="col-lg-3 ">	                    
            <layout:block name="menu_list">
            </layout:block>	
        </div>
        <div class="col-lg-9">
        	<div class="main-content">
            	<layout:block name="main_content">
            	</layout:block>
         </div>
        </div>
    </div>
</div>

<div id="envelope"></div>
<div id="message-list-box" class="hide">
	<div class="message-list-top">
		<span class="title">消息</span>
		<span class="glyphicon glyphicon-remove closed"></span>
		<span class="glyphicon glyphicon-user users"></span>
	</div>
	<div class="message-list"></div>
	<div class="message-list-bottom" id="write-message">
		<span>发信息</span>
	</div>
</div>

<div id="message-contacts-box" class="hide">
	<div class="message-contacts-top">
		<span class="title">联系人</span>
		<span class="glyphicon glyphicon-remove closed"></span>
	</div>
	<div class="message-contacts">
    	<h4>
        	<a class="contacts-expand collapsed" data-toggle="collapse" href="#admin-contacts" aria-expanded="false" aria-controls="admin-contacts">
          		<span class="glyphicon glyphicon-plus"></span>  管理员
        	</a>
      	</h4>
    	<div id="admin-contacts" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingOne">
      		<ul class="contacts-list-group list-group"></ul>
    	</div>
	    <h4>
	        <a class="contacts-expand collapsed" data-toggle="collapse" href="#teacher-contacts" aria-expanded="false" aria-controls="teacher-contacts">
	          	<span class="glyphicon glyphicon-plus"></span>  教师
	        </a>
	    </h4>
	    <div id="teacher-contacts" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingTwo">
	      	<ul class="contacts-list-group list-group"></ul>
	    </div>
	    <h4>
	        <a class="contacts-expand collapsed" data-toggle="collapse" href="#student-contacts" aria-expanded="false" aria-controls="student-contacts">
	          	<span class="glyphicon glyphicon-plus"></span>  学生
	        </a>
	    </h4>
	    <div id="student-contacts" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingTwo">
	      	<ul class="contacts-list-group list-group"></ul>
	    </div>
	</div>
</div>

<div id="message-content-box" class="hide" from=<s:property value="#session.user_id"/>>
	<div class="message-content-top">
		<span class="title">某某某</span>
		<span class="glyphicon glyphicon-remove closed"></span>
		<span class="glyphicon glyphicon-user users"></span>
		<span class="glyphicon glyphicon-menu-left back"></span>
	</div>
	<div class="message-content"></div>
	<div class="message-tool"></div>
	<div class="message-writeboard">
		<textarea class="form-control" rows="4"></textarea>
		<div class="send-bottom">
			<button type="button" class="btn btn-sm" onclick="sendMessage()">发送</button>
		</div>
	</div>
</div>

<script type="text/javascript" src="/js/base/websocket.js"></script>
        
 <layout:block name="nav_content">
 
 </layout:block>
	

	
	
</layout:override>


<%@ include file="/jsp/base/base.jsp" %>


   	