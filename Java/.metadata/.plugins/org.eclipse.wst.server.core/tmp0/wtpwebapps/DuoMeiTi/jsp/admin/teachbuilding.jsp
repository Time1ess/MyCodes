<%@ include file="/jsp/base/taglib.jsp" %>

<layout:override name="main_content">
	<script type='text/javascript' src="/js/admin/teachbuilding.js"></script>
	<div class="mycontent">
		<div class="row">
			<div class="col-lg-6 col-lg-offset-3 classbuilding">
				<span>教学楼管理</span>
			</div>
		</div>
		<hr>
		<!-- Modal -->
		<div class="modal fade" id="teachBuildingModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
		  <div class="modal-dialog" role="document">
		    <div class="modal-content">
		      <div class="modal-header">
		        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
		        <h4 class="modal-title" id="myModalLabel">新增教学楼</h4>
		      </div>
		      <div class="modal-body">
			      <form class="form-horizontal">
				        <div class="form-group">
							<label class="control-label col-sm-3" for="input_buildName_num">教学楼</label>
							<div class="col-sm-5">
								<input type="text" class="form-control" id="input_buildName_num">
								<!-- <p class="help-block">字母，数字，汉字皆可</p> -->
							</div>
							<div style="text-align:center" class="col-sm-4 control-label">
								<span id="exist"></span>
							</div>
						</div>
					</form>
		      </div>
		      <div class="modal-footer">
		        <button type="button" class="btn btn-default" data-dismiss="modal">取消</button>
		        <button type="button" class="btn btn-primary" onclick="addTeachBuilding()">确定新增</button>
		      </div>
		    </div>
		  </div>
		</div>
		<div>
			<button type="button" class="btn btn-primary btn-lg" onclick="add()">
			 	 新增教学楼
			</button>
		</div>
		<div class="container-fluid">
			<s:iterator value="builds" var="build" status="i">
				<div class="col-lg-4">
					<a href="classroom_manage?build_id=<s:property value="#build.build_id"/>&build_name=<s:property value="#build.build_name"/>">
						<div class="teachbuilding-div"><s:property value="#build.build_name"/></div>
					</a>
				</div>
			</s:iterator>
		</div>
	</div>
	<style>
		.teachbuilding-div {
			margin: 10%;
			height:100px;
			line-height:100px;
			border:1px solid black;
			text-align:center;
		}
	</style>
</layout:override>


<%@ include file="base.jsp" %>