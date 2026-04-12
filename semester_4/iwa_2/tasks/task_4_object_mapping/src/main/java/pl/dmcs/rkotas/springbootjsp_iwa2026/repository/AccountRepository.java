package pl.dmcs.rkotas.springbootjsp_iwa2026.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import pl.dmcs.rkotas.springbootjsp_iwa2026.model.Account;

@Repository
public interface AccountRepository extends JpaRepository<Account, Long> {

}
