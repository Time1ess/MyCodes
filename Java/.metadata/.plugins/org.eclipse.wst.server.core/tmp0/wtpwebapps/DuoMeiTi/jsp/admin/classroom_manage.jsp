<%@page import="java.util.ArrayList,model.Classroom"%>
<%@ include file="/jsp/base/taglib.jsp" %>

<layout:override name="main_content">
<script type='text/javascript' src="/js/admin/classroom_manage.js"></script>
<script type="text/javascript">
	/*$(function () { 
		$('#classroom-modal').modal({
			backdrop: 'static', 
			keyboard: false
	 	})
	 });*/
</script>
<div class="mycontent">
  <div class="row">
    <div class="col-lg-6 col-lg-offset-3 classbuilding ">
      <span id="build_name"><s:property value="build_name"/></span>教学楼
    </div>
  </div>
  <hr>
  <form class="form-horizontal" id="classroom_search_form">
    <div class="form-horizontal">
        <div class="form-group">
        
            <label class="col-lg-2 control-label" style="margin:2px">教室查询：</label>
            
            
            <div class="col-lg-2">
                <select class="col-lg-2 form-control" style="margin:3px;"name="searchselect" id="searchselect">
                <option value="1">教室号</option>
                <option value="2">负责人</option>
            </select>
            </div>
            
			<div class="col-lg-2">
				<input type="text" class="col-lg-3 form-control" style="margin:3px;height:34px;" aria-describedby="basic-addon1" name="search" id="query_condition">
			</div>

			<div class="col-lg-1">
                <button type="button" class="btn btn-primary" style="margin:2px;" id="sc_button" onclick="queryclassrooms()">查&nbsp;&nbsp;询</button>
            </div>
            <div class="col-lg-2">
            	<button type="button" class="btn btn-primary" style="margin:2px;" id="all_button" onclick="queryAll()">所&nbsp;有&nbsp;教&nbsp;室</button>
            </div>
            <div class="col-lg-1">
            	<button type="button" class="btn btn-danger" style="margin:2px;" id="add_button" onclick="add_classroom()">新&nbsp;增&nbsp;教&nbsp;室</button>
            </div>
        </div>
    </div>
  </form>
  
    <!-- Modal -->
	<div class="modal fade" id="classroom-modal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
	  <div class="modal-dialog">
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
	        <h4 class="modal-title" id="myModalLabel">添加教室</h4>
	      </div>
	      <div class="modal-body">
			<form class="form-horizontal">
				<input style="visibility:hidden" id="submit_type" value="add" />
				<div class="form-group">
					<label class="control-label col-sm-3" for="input_classroom_num">教室号</label>
					<div class="col-sm-5">
						<input type="text" class="form-control" id="input_classroom_num">
						<!-- <p class="help-block">字母，数字，汉字皆可</p> -->
					</div>
					<div style="text-align:center" class="col-sm-4 control-label">
						<span id="exist"></span>
					</div>
				</div>
				<div class="form-group">
					<label class="control-label col-sm-3" for="input_principal_student_id">负责人</label>
					<div class="col-sm-5">
						<input type="text" class="form-control" id="input_principal_student_id" oninput="disable_add_btn()">
					</div>
					<div style="text-align:center" class="col-sm-4 control-label">
						<span id="input_principal_student_name">lz</span>
					</div>
					<!-- <div class="col-sm-3">
						<button class="btn btn-primary" onclick="query_stu_name()">查询姓名</button>
					</div> -->
				</div>
			</form>
			</div>
	      <div class="modal-footer">
	        <button class="btn btn-success" onclick="query_stu_name()">查询负责人姓名</button>
	        <button type="button" class="btn btn-default" data-dismiss="modal">取消</button>
	        <button type="button" class="btn btn-primary" id="add_classroom_btn" onclick="classroom_submit()">确定添加</button>
	      </div>
	    </div>
	  </div>
	</div>
	
	
  
  <div id="classroom_search_table">
    <table class="table table-bordered table-striped" id="classroom_table">
      <thead>
        <tr>
            <th>教室号</th>
            <th>设备</th>
            <!-- <th>教室大小</th> -->
            <th>负责人</th>
            <th>编辑</th>
            <th>管理教室</th>
        </tr>
      </thead>

      <s:iterator value="classrooms" var="classroom" status="i">  
			<tr class="success" classroom_id=<s:property value="#classroom.id"/> >
				<td>   <s:property value="#classroom.classroom_num"/>    </td>
				<td width="40%">   <s:property value="#classroom.repertorys"/>    </td>
				<%-- <td>   <s:iterator value="#classroom.repertorys" var="rt"> <s:property value="#rt.rtType"/>&nbsp;&nbsp;&nbsp;</s:iterator>   </td> --%>
				<%-- <td>   <s:property value="#classroom.capacity"/>    </td> --%>
				<td studId="<s:property value="#classroom.principal_stuId"/>">   <s:property value="#classroom.principal_name"/>    </td>
				<td>   <a class="btn btn-info" onclick="edit_classroom(<s:property value="#i.index"/>)">编&nbsp;&nbsp;辑</a></td>
				<td>   <a href="classroom_detail?classroomId=<s:property value="#classroom.id"/>&build_name=<s:property value="build_name"/>" class="btn btn-info">详&nbsp;&nbsp;细</a>    </td>
				<%-- <td> <a class="btn btn-info" onclick="mypost(<s:property value="#i.index"/>)">详&nbsp;&nbsp;细</a></td> --%>
			</tr>
		</s:iterator>
      
      
    </table>
  </div>
		<pt:pageInfo
			pageCount="${pageBean.pageCount }"
			currPage="${pageBean.currPage }"
			param="currPage" 
			path="${path}"
			totalPage="${pageBean.lastPage }" 
			pageSize="${pageBean.pageSize }"
			totalSize="${pageBean.totalSize }" 
		/>
		<%-- <span style="visibility:hidden" id="pageSize"><s:property value="pageSize"/></span> --%>
	</div>

</layout:override>

<%@ include file="/jsp/admin/base.jsp" %>