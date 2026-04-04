package model;

import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Set;

public class Row {
    // Używamy LinkedHashMap, aby zachować kolejność kolumn przy wyświetlaniu
    private final Map<String, String> data;

    public Row() {
        this.data = new LinkedHashMap<>();
    }

    public Row(Map<String, String> data) {
        this.data = new LinkedHashMap<>(data);
    }

    public void put(String column, String value) {
        data.put(column, value);
    }

    public String get(String column) {
        return data.get(column);
    }

    public Set<String> getColumns() {
        return data.keySet();
    }

    public Map<String, String> getData() {
        return new LinkedHashMap<>(data);
    }

    @Override
    public String toString() {
        return data.toString();
    }
}