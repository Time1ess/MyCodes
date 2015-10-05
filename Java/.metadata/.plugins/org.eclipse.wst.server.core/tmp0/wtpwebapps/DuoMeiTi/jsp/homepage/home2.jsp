<%@ include file="/jsp/base/taglib.jsp" %>

<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<html lang="en">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
    <meta name="renderer" content="webkit">
    <title>多媒体管理系统</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    
    <meta name="description" content="">
    
    <meta name="keywords" content="">
    <meta name="author" content="">
    <!-- CSS Config. -->

    
 <!-- Le styles -->
 
         <link href="/bootstrap/css/bootstrap.min.css" rel="stylesheet" />
		<link href="/bootstrap/css/bootstrap-theme.min.css" rel="stylesheet" />		
		<link href="/datepicker/css/bootstrap-datetimepicker.min.css" rel="stylesheet" />
        <script type='text/javascript' src="/js/base/jquery-2.1.4.min.js"></script>
        <script type='text/javascript' src="/datepicker/js/bootstrap-datetimepicker.min.js"></script>
		<script type="text/javascript" src="/datepicker/js/bootstrap-datetimepicker.zh-CN.js" charset="UTF-8"></script>
 
<!-- <link href="/new_homepage/bootstrap/assets/css/bootstrap.min.css" rel="stylesheet"> -->
<!-- <link href="/new_homepage/bootstrap/assets/css/bootstrap-theme.min.css" rel="stylesheet"> -->

<link rel="stylesheet" type="text/css" media="screen" href="/new_homepage/style/common/base.css">
<link rel="stylesheet" type="text/css" media="screen" href="/new_homepage/style/common/content.css">
<link rel="stylesheet" type="text/css" media="screen" href="/new_homepage/style/home/content.css">
<!-- <script type="text/javascript" src="/new_homepage/bootstrap/assets/js/jquery-1.10.2.min.js"></script><style type="text/css" adt="123"></style> -->
<!-- ajax_csrf-->
<!-- <script type="text/javascript" src="/new_homepage/js/ajax_csrf.js"></script> -->



 
    






<style type="text/css">object,embed{                -webkit-animation-duration:.001s;-webkit-animation-name:playerInserted;                -ms-animation-duration:.001s;-ms-animation-name:playerInserted;                -o-animation-duration:.001s;-o-animation-name:playerInserted;                animation-duration:.001s;animation-name:playerInserted;}                @-webkit-keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}                @-ms-keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}                @-o-keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}                @keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}</style></head>

  <body>
  <a href="/">
				<div id="headerpic" style="height:80px;">
				</div>
			</a>
    <div class="container" id="nav-container">

	       
	       
       <!--head content-->
       <div class="masthead">
	         <!--Head title-->
<!-- 	         <a href="/"><h1 class="muted head-title">大连理工大学基本科研业务费管理平台</h1></a> -->
<!-- 	         <p class="head-title-low">Dalian University of Technology Fundamental Research Fund Management Platform</p> -->
<!-- 	         <hr class="head-hr"> -->
			        
			   <div class="container">
			     <nav class="navbar navbar-default" role="navigation">
			       <div class="collapse navbar-collapse">
			         <ul class="nav navbar-nav">
			           <li class=""><a href="/">首页</a></li>
			           <li class=""><a href="">教室视频</a></li>
			           <li class=""><a href="">通讯录</a></li>
			           <li class=""><a href="">常见问题</a></li>
			           
			           
			           
			           <li class=""><a href="/login">登录</a></li>
			           <li class="dropdown">
			             <a href="#" class="dropdown-toggle" data-toggle="dropdown">注册
			               <b class="caret"></b>
			             </a>
			             <ul class="dropdown-menu home_menu" role="menu">
			               <li><a href="/admin_register">系统管理员</a></li>
			               <li><a href="/student_register">在职学生</a></li>
			               <li><a href="/accounts/expertlogin">授课教师</a></li>			               
			             </ul>
			           </li>
			           
			           
			         </ul>
			       </div>
			     </nav>
			   </div><!--end navbar-->
   
       </div><!--end mashhead-->
    </div><!--end whole container-->
    
    
   <!--different page content-->
   
<div class="homepage-picture">
  <div id="myCarousel" class="carousel slide" style="width:100%; height:300px">
  <div class="carousel-inner" style="height:100%">
    
      <div class="item  active ">
        <img src="/new_homepage/homepage_pic/2.jpg" alt="">
        <div class="carousel-caption">
        </div>
      </div>
    
  </div>
  <div class="left my-carousel-control">
    <a class="" href="/#myCarousel" data-slide="prev">‹</a>
  </div>
  <div class="right my-carousel-control">
    <a class="" href="/#myCarousel" data-slide="next">›</a>
  </div>
</div>
<!-- /.carousel -->

</div>

<div class="container home-content-container">
     
				
				
<div class="row news_frame">
  <div class="col-lg-6">
    <!--news base template-->
		<div class="">
		  <div class="front-wrap">
		    <div class="home-news">
		      <div class="usoft-listview-header">
		        <h3>通知公告          <small>announcement </small> </h3>
		        <span class="usoft-listview-more">						          
					<strong><a href="home/news/news_cate=announcement">更多»</a></strong>						
		        </span>
		      </div>
		      
		      <div class="news-list">
		      
		      
		        <div class="news-documents documents-list "> 
					<div class="usoft-listview-basic">
					  <ul>
					    <li>
					      <span class="usoft-listview-item-date">12-30</span>
					      <span><a href="home/news/4" title="关于用户名的说明">关于用户名的说明</a></span>
					    </li>
					  </ul>
					</div>
					
					<div class="usoft-listview-basic">
					  <ul>
					    <li>
					      <span class="usoft-listview-item-date">12-10</span>
					      <span><a href="home/news/3" title="专项项目申报的通知">关于表扬李四同学</a></span>
					    </li>
					  </ul>
					</div>
		
		
		        </div><!--end news-documents-->
		      </div><!--end news-list-->
		      
		    </div><!--home-news-->
		  </div><!--front wrap-->
		</div>

  </div>  <!--<div class="col-lg-6"> -->
  
  
  <div class="col-lg-6">
    <!--important news-->
			<!--news base template-->
			<div class="">
			  <div class="front-wrap">
			    <div class="home-news">
			      <div class="usoft-listview-header">
			        <h3>检查教室 <small>check-classroom</small> </h3>
			        <span class="usoft-listview-more">
						<strong><a href="home/news/news_cate=documents">更多»</a></strong>
			        </span>
			      </div>
			      
			      <div class="news-list">
			        <div class="news-documents documents-list ">
							
							
							
							
							
						<s:iterator value="check_list" var="i" status="index" >   
						
						   <div class="usoft-listview-basic">
							  <ul>
							    <li>
							      <span class="usoft-listview-item-date">01-08</span>
							      <span><a href="" title="">
							      		<s:property value="#i.classroom.classroom_num"/>
							      		检查
							      		<s:property value="#i.checkman.user.username"/>
							      		</a>
							      </span>
							    </li>
							  </ul>
							</div>
							
						</s:iterator>
							
							
							
							
							
						  <div class="usoft-listview-basic">
							  <ul>
							    <li>
							      <span class="usoft-listview-item-date">01-08</span>
							      <span><a href="" title="">张三检查一馆301:&nbsp;教室无问题</a></span>
							    </li>
							  </ul>
							</div>
							
							
						  
							
							
							<div class="usoft-listview-basic">
							  <ul>
							    <li>
							      <span class="usoft-listview-item-date">01-08</span>
							      <span><a href="" title="">张三检查一馆301:&nbsp;教室无问题</a></span>
							    </li>
							  </ul>
							</div>
							
							<div class="usoft-listview-basic">
							  <ul>
							    <li>
							      <span class="usoft-listview-item-date">12-10</span>
							      <span><a href="A5.zip" title="2015p">王二检查212:&nbsp;教室电脑坏掉</a></span>
							    </li>
							  </ul>
							</div>
			
			
			        </div><!--end news-documents-->
			      </div><!--end news-list-->
			      
			    </div><!--home-news-->
			  </div><!--front wrap-->
			</div>

  </div>
</div>
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
<div class="row news_frame">
  <div class="col-lg-12">
    <!--news base template-->
		<div class="">
		  <div class="front-wrap">
		    <div class="home-news">
		      <div class="usoft-listview-header">
		        <h3>设备维修记录          <small>Equipment- maintenance -records </small> </h3>
		        <span class="usoft-listview-more">					          
				<strong><a href="home/news/news_cate=announcement">更多»</a></strong>						
		        </span>
		      </div>						      
		      <div class="news-list">
		        <div class="news-documents documents-list "> 
					<div class="usoft-listview-basic">
					  <ul>
					    <li>
					      <span class="usoft-listview-item-date">12-30</span>
					      <span><a href="home/news/4" title="关于用户名的说明">张三维修一馆301教室主机:&nbsp;已经修好</a></span>
					    </li>
					  </ul>
					</div>									
					<div class="usoft-listview-basic">
					  <ul>
					    <li>
					      <span class="usoft-listview-item-date">12-10</span>
					      <span><a href="home/news/3" title="专项项目申报的通知">田七维修二馆777教室USB线:&nbsp;已经替换为新的</a></span>
					    </li>
					  </ul>
					</div>					
		        </div><!--end news-documents-->
		      </div><!--end news-list-->
		      
		    </div><!--home-news-->
		  </div><!--front wrap-->
		</div>				
  </div>  <!--<div class="col-lg-6"> -->
  

</div>
				

				
				
				<!--check the browser type-->
				<div style="width:45%;background-color:#f2dede;border-color: #d6e9c6;" id="myModal" class="modal hide fade" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
						  <div style="border: 1px solid #fc6;text-align:center;">
						    <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
						    <h3>欢迎您使用创新创业管理平台</h3>
						  </div>
						  <div>
						    <div style="font-size:20px;padding:20px;margin-bottom:0px;">
						      <p class="text-info">为了达到最佳浏览效果，我们推荐您使用以下浏览器</p>
						      <p style="font-size:14px;color:#3a87ad">请您<strong>点击</strong>相应的浏览器图标跳转到下载页面进行下载
						    </p></div>
						  </div>
						  <hr style="border-bottom: 1px solid #FFFF99;margin:0px;">
						  <div style="font-size:20px;padding:20px;margin:10px;">
						    <form class="bs-docs-example">
						      <center>
						        <a href="http://chrome.360.cn/" style="margin-right:15px;">
						            <img border="0" style="width:70px;height:70px;" src="/new_homepage/images/360.jpg" title="360极速浏览器(下载快速)"> 
						        </a>
						        <a href="http://www.google.cn/intl/zh-CN/chrome/browser/" style="margin-right:15px;">
						          <img border="0" style="width:70px;height:70px;" src="/new_homepage/images/chrome.png" title="谷歌浏览器(使用最广)">
						        </a>
						        <a href="http://www.maxthon.cn/" style="margin-right:15px;">
						          <img border="0" style="width:70px;height:70px;" src="/new_homepage/images/maxthon-logo.png" title="傲游浏览器"> 
						        </a>
						        <a href="http://firefox.com.cn/download/" style="margin-right:15px;">
						          <img border="0" style="width:70px;height:70px;" src="/new_homepage/images/browser-icon-firefox.png" title="火狐浏览器"> 
						        </a>
						        <a href="http://www.opera.com/zh-cn/computer/windows" style="margin-right:15px;">
						          <img border="0" style="width:70px;height:70px;" src="/new_homepage/images/Opera.png" title="Opera浏览器"> 
						        </a>
						        <a href="http://ie.sogou.com/" style="margin-right:15px;">
						          <img border="0" style="width:70px;height:70px;" src="/new_homepage/images/sogou.jpg" title="搜狗浏览器"> 
						        </a>
						      </center>
						    </form>
						  </div>
						  <hr style="border-top: 1px solid #FFFF99;margin:0px;">
						  <div style="font-size:20px;padding:20px;margin-bottom:0px;">
						    <p style="font-size:18px;" class="text-success">如果您选择使用<strong>360极速浏览器</strong>或是<strong>搜狗浏览器</strong>，我们建议您将浏览器设置为<strong>极速模式</strong>。</p>
						  </div>
				</div>
				<script type="text/javascript" src="/new_homepage/js/home/checkbrowser.js"></script>
				

   </div>
   
 <div id="footer-links">
     <!--useful links-->
		<br>
		<p class="item-title-white">友情链接</p>
		<hr class="head-hr">
		<div class="row-fluid" id="home-linker">
		  <div class="col-lg-3">
		    <a href="http://www.dlut.edu.cn/">大连理工大学</a>
		  </div>
		</div>

</div>
   
   

    
    
    <!-- FOOTER -->
<footer class="container">
  <p>Copyright © 1986 - 2016 All rights reserved | | GPLv3 <a href="http://gplv3.fsf.org/">Terms</a></p>
</footer>

<!--End FOOTER-->


    
    
   
<!-- Le javascript
================================================== -->
<!-- Placed at the end of the document so the pages load faster -->
<!-- <script type="text/javascript" src="/new_homepage/bootstrap/assets/js/bootstrap.min.js"></script> -->
<script type='text/javascript' src="/bootstrap/js/bootstrap.min.js"></script>

<!--TinyMCE Editor-->
<!-- <script type="text/javascript" src="/new_homepage/tiny_mce/tiny_mce.js"></script> -->
<script type='text/javascript' src="/js/base/tiny_mce.js"></script>
<!-- JQuery Masonry-->
<script type='text/javascript' src="/js/base/jquery.masonry.min.js"></script>

<!-- JQuery Masonry-->
<!-- <script type="text/javascript" src="/new_homepage/masonry/jquery.masonry.min.js"></script> -->

    
<script type="text/javascript" src="/new_homepage/js/features.js"></script>
   
    
    
    
    <!-- 百度推广JS -->
    <script type="text/javascript">
  var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F467a2b45543928de4d32a9f7c3bfc175' type='text/javascript'%3E%3C/script%3E"));
    </script><script src=" http://hm.baidu.com/h.js?467a2b45543928de4d32a9f7c3bfc175" type="text/javascript"></script><a href="http://tongji.baidu.com/hm-web/welcome/ico?s=467a2b45543928de4d32a9f7c3bfc175" target="_blank"><img border="0" src="http://eiv.baidu.com/hmt/icon/21.gif" width="20" height="20"></a>
    <!-- 百度推广JS END -->
  

</body></html>