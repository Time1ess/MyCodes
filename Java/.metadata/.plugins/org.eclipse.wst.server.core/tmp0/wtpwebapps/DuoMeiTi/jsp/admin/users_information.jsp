<%@ include file="/jsp/base/taglib.jsp" %>


<layout:override name="main_content">
	<div class="mycontent">
		<br/>
		
		<form class="form-inline"  method="POST" id="student_register_form">
		 	<div class="form-group col-lg-offset-1">
		    	<label for="username">用&nbsp;&nbsp;户&nbsp;&nbsp;名：</label>
		 		<input type="text" class="form-control" id="username" name="username" placeholder="uername" readonly>
			</div>
			<div class="form-group col-lg-offset-1">
		    	<label for="college">所在院系:</label>
		    	<s:select list="collegeSelect" class="form-control" name="college"></s:select>
			</div>
			<br>
			<br>
			<br>
			<div class="form-group col-lg-offset-1">
		    	<label for="fullName">姓&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;名：</label>
		 		<input type="text" class="form-control" id="fullName" name="fullName" placeholder="name">
			</div>
			<div class="form-group col-lg-offset-1">
		    	<label for="phoneNumber">联系方式:</label>
		    	<input type="text" class="form-control"  id="phoneNumber" name="phoneNumber" placeholder="1848451512">
			</div>
			<br>
			<br>
			<br>
			<div class="form-group col-lg-offset-1">
		    	<label for="studentId">学&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;号：</label>
		 		<input type="text" class="form-control"  id="studentId" name="studentId" placeholder="2152451">
			</div>
			<div class="form-group col-lg-offset-1">
		    	<label for="bankCard">银行卡号:</label>
		    	<input type="text" class="form-control"  id="bankCard" name="bankCard" placeholder="635656515545214521455">
			</div>
			<br>
			<br>
			<br>
			<div class="form-group col-lg-offset-1">
			  	<label for="idCard">身&nbsp;&nbsp;份&nbsp;&nbsp;证：</label>
			  	<input type="text" class="form-control" id="idCard" name="idCard" value="" placeholder="21142156562562">
			</div>
			<div class="form-group col-lg-offset-1">
				<label for="entryTime">入职时间：</label>
			  	<input type="date" class="form-control" id="entryTime" name="entryTime" value="" placeholder="2015">
			</div>
			<br>
			<br>
			<br>
			  
			
			<div class="form-group col-lg-offset-1">
				<label for="classrooms">负责教室：</label>
			  	<input type="text" class="form-control" id="classrooms" name="classrooms" value="" placeholder="hf481">
			</div>
			<div class="form-group col-lg-offset-1">
				<label for="sex">性&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;别</label>
			  	<select  class="form-control">
		    		<option>男</option>
					<option>女</option>
		    	</select>
			</div>  
			<br>
			<br>
			<br>
		
			<button type="button" class="btn btn-success" id="change">修改</button>
		  
		</form>
		
		
		
		<script>
		$(document).on('click',"#change",function(){
			alert("Hello！");
		})
		
		</script>
		
		
	</div>
</layout:override>



<%@ include file="/jsp/admin/base.jsp" %>