<%@ include file="/jsp/base/taglib.jsp" %>

<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

   
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">


<html lang="en">
    <head>
        <meta charset="utf-8"/>
        <meta name="renderer" content="webkit"/>
        <title>多媒体管理系统</title>
        <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
        <meta name="keywords" content="" />
        <meta name="author" content="" />
        <link href="/bootstrap/css/bootstrap.min.css" rel="stylesheet" />
		<link href="/bootstrap/css/bootstrap-theme.min.css" rel="stylesheet" />
		<link rel="stylesheet" type="text/css" media="screen" href="/css/base/table.css" >		
		<link rel="stylesheet" type="text/css" media="screen" href="/css/base/base.css"/> 
		<link rel="stylesheet" type="text/css" media="screen" href="/css/admin/classroom_manage.css"/>
		<link rel="stylesheet" type="text/css" media="screen" href="/css/admin/repertory.css"/>
		<link href="/datepicker/css/bootstrap-datetimepicker.min.css" rel="stylesheet" />
        <script type='text/javascript' src="/js/base/jquery-2.1.4.min.js"></script>
        <script type='text/javascript' src="/datepicker/js/bootstrap-datetimepicker.min.js"></script>
		<script type="text/javascript" src="/datepicker/js/bootstrap-datetimepicker.zh-CN.js" charset="UTF-8"></script>
		<style>
				td,tr,th{
				text-align:center;
				vertical-align:middle;
				}
		</style>
    </head>   

<body>
	<div class="mycontent">
		<div id="maintainRecords_table">
			<table class="table table-bordered table-striped"
				id="Records_table">
				<thead>
					<tr>
						<th style="width:10%;">学号</th>
						<th style="width:10%;">姓名</th>
						<th style="width:10%;">设备</th>
						<th style="width:40%;">维修情况</th>
						<th style="width:10%;">日期</th>
						<th style="width:10%;">教室</th>
						<th style="width:10%;">教学楼</th>
					</tr>
				</thead>
				
				<s:iterator value="#session.maintainRecords_list" var="item">
					<tr class="success" id='<s:property value="#item.id"/>'>
						<td><s:property value="#item.studentId" /></td>
						<td><s:property value="#item.fullName" /></td>
						<td><s:property value="#item.rtType" /></td>
						<td><s:property value="#item.repairDetail" /></td>
						<td><s:property value="#item.repairDate" /></td>
						<td><s:property value="#item.classRoom" /></td>
						<td><s:property value="#item.teachBuilding" /></td>

						</td>
					</tr>
				</s:iterator>


			</table>
		</div>
	</div>

</body>
</html>>