package pl.dmcs.rkotas.task3.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import pl.dmcs.rkotas.task3.model.Student;

@Repository
public interface StudentRepository extends JpaRepository<Student, Long> {
    Student findById(long id);
}