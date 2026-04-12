package pl.dmcs.rkotas.springbootjsp_iwa2026.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.rkotas.springbootjsp_iwa2026.model.Address;
import pl.dmcs.rkotas.springbootjsp_iwa2026.repository.AddressRepository;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/addresses")
public class AddressRESTController {

    private final AddressRepository addressRepository;

    @Autowired
    public AddressRESTController(AddressRepository addressRepository) {
        this.addressRepository = addressRepository;
    }

    @GetMapping
    public List<Address> findAllAddresses() {
        return addressRepository.findAll();
    }

    @GetMapping("/{id}")
    public ResponseEntity<Address> getAddressById(@PathVariable Long id) {
        Optional<Address> address = addressRepository.findById(id);
        if (address.isPresent()) {
            return new ResponseEntity<>(address.get(), HttpStatus.OK);
        } else {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }

    @PostMapping
    public ResponseEntity<Address> addAddress(@RequestBody Address address) {
        Address savedAddress = addressRepository.save(address);
        return new ResponseEntity<>(savedAddress, HttpStatus.CREATED);
    }

    @PutMapping("/{id}")
    public ResponseEntity<Address> updateAddress(@PathVariable Long id, @RequestBody Address addressDetails) {
        Optional<Address> addressData = addressRepository.findById(id);

        if (addressData.isPresent()) {
            Address existingAddress = addressData.get();

            existingAddress.setCity(addressDetails.getCity());
            existingAddress.setStreet(addressDetails.getStreet());
            existingAddress.setNumber(addressDetails.getNumber());
            existingAddress.setPostalCode(addressDetails.getPostalCode());

            Address updatedAddress = addressRepository.save(existingAddress);
            return new ResponseEntity<>(updatedAddress, HttpStatus.OK);
        } else {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteAddress(@PathVariable Long id) {
        if (addressRepository.existsById(id)) {
            addressRepository.deleteById(id);
            return new ResponseEntity<>(HttpStatus.NO_CONTENT);
        } else {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }

}