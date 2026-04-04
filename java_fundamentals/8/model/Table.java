package model;

import java.util.ArrayList;
import java.util.List;

public class Table {
    private String name;
    private List<Row> rows;

    public Table(String name) {
        this.name = name;
        this.rows = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    public List<Row> getRows() {
        return rows;
    }

    public void insert(Row row) {
        rows.add(row);
    }

    public void delete(Row row) {
        rows.remove(row);
    }

    public void setRows(List<Row> newRows) {
        this.rows = newRows;
    }
}