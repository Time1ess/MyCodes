<%@ include file="/jsp/base/taglib.jsp" %>



<layout:override name="main_content">
	

    <div class="mynavbar">
        <div class="container-fluid nopadding">
		    <div class="row nomargin">
		        <div class="col-lg-3 nopadding">
		           <a href="/adminStaff/classInfo/classList" class="navbar-button navbar-button-left">课程名单查询</a> 
		        </div>
		        <div class="col-lg-3 nopadding">
		           <a href="/adminStaff/classInfo/scoreList" class="navbar-button">课程成绩查询</a> 
		        </div>
		        <div class="col-lg-3 nopadding">
		           <a href="/adminStaff/classInfo/studentList" class="navbar-button">学生成绩查询</a> 
		        </div>
		
		        <div class="col-lg-3 nopadding">
		           <a href="/adminStaff/classInfo/scoreSearch" class="navbar-button navbar-button-right">学生成绩搜索</a> 
		        </div>
		    </div>
		</div>

    </div>
    <div class="mycontent">
        	你自己定义吧
    </div>
	
	

</layout:override>








<%@ include file="/jsp/admin/base.jsp" %>
