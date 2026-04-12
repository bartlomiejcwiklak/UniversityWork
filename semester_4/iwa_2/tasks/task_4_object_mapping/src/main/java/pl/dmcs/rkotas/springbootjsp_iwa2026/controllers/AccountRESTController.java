package pl.dmcs.rkotas.springbootjsp_iwa2026.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.rkotas.springbootjsp_iwa2026.model.Account;
import pl.dmcs.rkotas.springbootjsp_iwa2026.repository.AccountRepository;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/accounts")
public class AccountRESTController {

    private final AccountRepository accountRepository;

    @Autowired
    public AccountRESTController(AccountRepository accountRepository) {
        this.accountRepository = accountRepository;
    }

    @GetMapping
    public List<Account> findAllAccounts() {
        return accountRepository.findAll();
    }

    @GetMapping("/{id}")
    public ResponseEntity<Account> getAccountById(@PathVariable Long id) {
        Optional<Account> account = accountRepository.findById(id);
        if (account.isPresent()) {
            return new ResponseEntity<>(account.get(), HttpStatus.OK);
        } else {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }

    @PostMapping
    public ResponseEntity<Account> addAccount(@RequestBody Account account) {
        Account savedAccount = accountRepository.save(account);
        return new ResponseEntity<>(savedAccount, HttpStatus.CREATED);
    }

    @PutMapping("/{id}")
    public ResponseEntity<Account> updateAccount(@PathVariable Long id, @RequestBody Account accountDetails) {
        Optional<Account> accountData = accountRepository.findById(id);

        if (accountData.isPresent()) {
            Account existingAccount = accountData.get();
            // Aktualizujemy nazwę konta
            existingAccount.setAccountName(accountDetails.getAccountName());

            Account updatedAccount = accountRepository.save(existingAccount);
            return new ResponseEntity<>(updatedAccount, HttpStatus.OK);
        } else {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteAccount(@PathVariable Long id) {
        if (accountRepository.existsById(id)) {
            accountRepository.deleteById(id);
            return new ResponseEntity<>(HttpStatus.NO_CONTENT);
        } else {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }
}