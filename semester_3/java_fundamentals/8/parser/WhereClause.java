package parser;

import model.Row;

public class WhereClause {
    private final String column;
    private final String operator;
    private final String value;

    public WhereClause(String column, String operator, String value) {
        this.column = column;
        this.operator = operator;
        this.value = value;
    }

    public boolean matches(Row row) {
        String rowValue = row.get(column);
        
        if (rowValue == null) return false;

        try {
            double rowNum = Double.parseDouble(rowValue);
            double valNum = Double.parseDouble(value);
            return compareNumbers(rowNum, valNum);
        } catch (NumberFormatException e) {
            return compareStrings(rowValue, value);
        }
    }

    private boolean compareNumbers(double n1, double n2) {
        switch (operator) {
            case "=": return n1 == n2;
            case "!=": return n1 != n2;
            case ">": return n1 > n2;
            case "<": return n1 < n2;
            case ">=": return n1 >= n2;
            case "<=": return n1 <= n2;
            default: return false;
        }
    }

    private boolean compareStrings(String s1, String s2) {
        int comparison = s1.compareTo(s2);
        switch (operator) {
            case "=": return comparison == 0;
            case "!=": return comparison != 0;
            case ">": return comparison > 0;
            case "<": return comparison < 0;
            case ">=": return comparison >= 0;
            case "<=": return comparison <= 0;
            default: return false;
        }
    }
    
    @Override
    public String toString() {
        return column + " " + operator + " " + value;
    }
}