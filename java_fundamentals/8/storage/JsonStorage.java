package storage;

import exception.DatabaseException;
import model.Row;
import model.Table;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.Set;

public class JsonStorage {
    private static final String FILE_EXTENSION = ".json";

    public void saveTable(Table table) throws DatabaseException {
        String filename = table.getName() + FILE_EXTENSION;
        String jsonContent = serialize(table);
        
        try (FileWriter writer = new FileWriter(filename)) {
            writer.write(jsonContent);
        } catch (IOException e) {
            throw new DatabaseException("Could not save data to file: " + e.getMessage());
        }
    }

    public Table loadTable(String tableName) throws DatabaseException {
        String filename = tableName + FILE_EXTENSION;
        File file = new File(filename);

        if (!file.exists()) {
            return new Table(tableName);
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            StringBuilder content = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                content.append(line);
            }
            return deserialize(tableName, content.toString());
        } catch (IOException e) {
            throw new DatabaseException("Could not load data from file: " + e.getMessage());
        }
    }

    private String serialize(Table table) {
        StringBuilder json = new StringBuilder();
        json.append("[");
        List<Row> rows = table.getRows();
        for (int i = 0; i < rows.size(); i++) {
            Row row = rows.get(i);
            json.append("{");
            int colIndex = 0;
            Set<String> columns = row.getColumns();
            for (String col : columns) {
                String val = row.get(col)
                        .replace("\"", "\\\"")
                        .replace("\n", "\\n");
                
                json.append("\"").append(col).append("\":\"").append(val).append("\"");
                if (colIndex < columns.size() - 1) {
                    json.append(",");
                }
                colIndex++;
            }
            json.append("}");
            if (i < rows.size() - 1) {
                json.append(",");
            }
        }
        json.append("]");
        return json.toString();
    }

    private Table deserialize(String tableName, String json) {
        Table table = new Table(tableName);
        String content = json.trim();
        
        if (content.startsWith("[") && content.endsWith("]")) {
            content = content.substring(1, content.length() - 1);
        }
        
        if (content.isEmpty()) {
            return table;
        }

        String[] objects = content.split("},\\{");
        for (String obj : objects) {
            obj = obj.replace("{", "").replace("}", "");
            Row row = new Row();
            
            String[] pairs = obj.split("\",\"");
            
            for (String pair : pairs) {
                String[] entry = pair.split("\":\"");
                if (entry.length >= 2) {
                    String key = entry[0].replace("\"", "").trim();
                    
                    StringBuilder valueBuilder = new StringBuilder();
                    for(int k=1; k<entry.length; k++) {
                        if(k > 1) valueBuilder.append("\":\"");
                        valueBuilder.append(entry[k]);
                    }
                    
                    String value = valueBuilder.toString().replace("\"", "");
                    value = value.replace("\\\"", "\"").replace("\\n", "\n");
                    
                    row.put(key, value);
                }
            }
            table.insert(row);
        }
        return table;
    }
}