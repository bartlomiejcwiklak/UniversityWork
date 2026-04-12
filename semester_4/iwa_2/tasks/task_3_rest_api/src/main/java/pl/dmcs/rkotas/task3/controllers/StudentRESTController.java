package pl.dmcs.rkotas.task3.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.rkotas.task3.model.Student;
import pl.dmcs.rkotas.task3.repository.StudentRepository;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/students")
public class StudentRESTController {

    private final StudentRepository studentRepository;

    @Autowired
    public StudentRESTController(StudentRepository studentRepository) {
        this.studentRepository = studentRepository;
    }

    @RequestMapping(method = RequestMethod.GET/*, produces = "application/xml"*/)
    //@GetMapping
    public List<Student> findAllStudents() {
        return studentRepository.findAll();
    }

    @RequestMapping(method = RequestMethod.POST)
    //@PostMapping
    public ResponseEntity<Student> addStudent(@RequestBody Student student) {
        studentRepository.save(student);
        return new ResponseEntity<Student>(student, HttpStatus.CREATED);
    }

    @RequestMapping(value="/{id}", method = RequestMethod.DELETE)
    //@DeleteMapping("/{id}")
    public ResponseEntity<Student> deleteStudent (@PathVariable("id") long id) {
        Student student = studentRepository.findById(id);
        if (student == null) {
            System.out.println("Student not found!");
            return new ResponseEntity<Student>(HttpStatus.NOT_FOUND);
        }
        studentRepository.deleteById(id);
        return new ResponseEntity<Student>(HttpStatus.NO_CONTENT);
    }

    @RequestMapping(value="/{id}", method = RequestMethod.PUT)
    //@PutMapping("/{id}")
    public ResponseEntity<Student> updateStudent(@RequestBody Student student, @PathVariable("id") long id) {
        student.setId(id);
        studentRepository.save(student);
        return new ResponseEntity<Student>(student, HttpStatus.OK);
    }

    @RequestMapping(value="/{id}", method = RequestMethod.PATCH)
    //@PatchMapping("/{id}")
    public ResponseEntity<Student> updatePartOfStudent(@RequestBody Map<String, Object> updates, @PathVariable("id") long id) {
        Student student = studentRepository.findById(id);
        if (student == null) {
            System.out.println("Student not found!");
            return new ResponseEntity<Student>(HttpStatus.NOT_FOUND);
        }
        partialUpdate(student,updates);
        return new ResponseEntity<Student>(HttpStatus.NO_CONTENT);
    }

    private void partialUpdate(Student student, Map<String, Object> updates) {
        if (updates.containsKey("firstname")) {
            student.setFirstname((String) updates.get("firstname"));
        }
        if (updates.containsKey("lastname")) {
            student.setLastname((String) updates.get("lastname"));
        }
        if (updates.containsKey("email")) {
            student.setEmail((String) updates.get("email"));
        }
        if (updates.containsKey("telephone")) {
            student.setTelephone((String) updates.get("telephone"));
        }
        studentRepository.save(student);
    }

    // -------------------------------------------------------------------

    @GetMapping("/{id}")
    public ResponseEntity<Student> getStudentById(@PathVariable("id") long id) {
        Student student = studentRepository.findById(id);
        if (student == null) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        return new ResponseEntity<>(student, HttpStatus.OK);
    }

    @DeleteMapping
    public ResponseEntity<Void> deleteAllStudents() {
        studentRepository.deleteAll();
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }

    @PutMapping
    public ResponseEntity<List<Student>> replaceAllStudents(@RequestBody List<Student> students) {
        studentRepository.deleteAll();
        studentRepository.saveAll(students);
        return new ResponseEntity<>(students, HttpStatus.OK);
    }
}