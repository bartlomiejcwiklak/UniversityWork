package pl.dmcs.rkotas.springbootjsp_iwa2026.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.rkotas.springbootjsp_iwa2026.model.Student;
import pl.dmcs.rkotas.springbootjsp_iwa2026.repository.AddressRepository;
import pl.dmcs.rkotas.springbootjsp_iwa2026.repository.StudentRepository;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/students")
public class StudentRESTController {

    private StudentRepository studentRepository;
    private AddressRepository addressRepository;

    @Autowired
    public StudentRESTController(StudentRepository studentRepository, AddressRepository addressRepository) {
        this.studentRepository = studentRepository;
        this.addressRepository = addressRepository;
    }

    @RequestMapping(method = RequestMethod.GET/*, produces = "application/xml"*/)
    //@GetMapping
    public List<Student> findAllStudents() {
        return studentRepository.findAll();
    }

    @RequestMapping(method = RequestMethod.POST)
    //@PostMapping
    public ResponseEntity<Student> addStudent(@RequestBody Student student) {
        if (student.getAddress().getId() <= 0 )
        {
            addressRepository.save(student.getAddress());
        }
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

    @RequestMapping(method = RequestMethod.DELETE)
    //@DeleteMapping()
    public ResponseEntity<Student> deleteStudents() {
        studentRepository.deleteAll();
        return new ResponseEntity<Student>(HttpStatus.NO_CONTENT);
    }

    @RequestMapping(value="/{id}", method = RequestMethod.GET)
    //@GetMapping("/{id}")
    public ResponseEntity<Student> getOneStudent (@PathVariable("id") long id) {
        Student student = studentRepository.findById(id);
        if (student == null) {
            System.out.println("Student not found!");
            return new ResponseEntity<Student>(HttpStatus.NOT_FOUND);
        }
        return new ResponseEntity<Student>(student, HttpStatus.OK);
    }

}
