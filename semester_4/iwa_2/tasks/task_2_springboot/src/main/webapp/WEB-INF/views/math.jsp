<%@taglib uri="http://www.springframework.org/tags/form" prefix="form" %>
<html>
<head>
    <title>Math stuff</title>
    <style>
        * {
            font-family: Helvetica, sans-serif;
            padding: 0;
            margin: 0;
        }

        input[type=text]{
            padding: 5px;
            margin-top: 5px;
        }

        input[type=submit]{
            padding: 10px;
            margin-top: 5px;
        }

        body {
            margin: 30px;
        }

        hr {
            margin-top: 20px;
            margin-bottom: 20px;
        }
    </style>
</head>
<body>
<h3>Calculate function answers</h3>
<form:form method="post" action="calculatex1x2.html" modelAttribute="math">
    <form:label path="coeffa">a</form:label>
    <form:input path="coeffa" />
    <br>
    <form:label path="coeffb">b</form:label>
    <form:input path="coeffb" />
    <br>
    <form:label path="coeffc">c</form:label>
    <form:input path="coeffc" />
    <br>
    <input type="submit" value="Calculate"/>
</form:form>
<hr>
<h3>Calculate n-th Fibonacci element</h3>
<form:form method="post" action="calculatefibonacci.html" modelAttribute="math">
    <form:label path="fibonacciN">n</form:label>
    <form:input path="fibonacciN" />
    <br>
    <input type="submit" value="Calculate"/>
</form:form>
<hr>
<h2 style="color: blue;">
    ${calculationResult}
</h2>
</body>

</html>