<%@taglib uri="http://www.springframework.org/tags/form" prefix="form" %>
<html>
<head>
    <title>Add student</title>
</head>
<body>
<h1>${message}</h1>
<h2>Student</h2>
<form:form method="post" action="addStudent.html" modelAttribute="student">
    <form:label path="firstname">First name</form:label>
    <form:input path="firstname" />
    <br>
    <form:label path="lastname">Last name</form:label>
    <form:input path="lastname" />
    <br>
    <form:label path="email">Email</form:label>
    <form:input path="email" />
    <br>
    <form:label path="telephone">Telephone</form:label>
    <form:input path="telephone" />
    <br>
    <input type="submit" value="Add Student"/>
</form:form>
</body>

</html>