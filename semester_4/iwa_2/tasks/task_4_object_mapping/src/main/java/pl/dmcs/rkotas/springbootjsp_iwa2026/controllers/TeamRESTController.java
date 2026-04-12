package pl.dmcs.rkotas.springbootjsp_iwa2026.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.rkotas.springbootjsp_iwa2026.model.Team;
import pl.dmcs.rkotas.springbootjsp_iwa2026.repository.TeamRepository;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/teams")
public class TeamRESTController {

    private final TeamRepository teamRepository;

    @Autowired
    public TeamRESTController(TeamRepository teamRepository) {
        this.teamRepository = teamRepository;
    }

    @GetMapping
    public List<Team> findAllTeams() {
        return teamRepository.findAll();
    }

    @GetMapping("/{id}")
    public ResponseEntity<Team> getTeamById(@PathVariable Long id) {
        Optional<Team> team = teamRepository.findById(id);
        if (team.isPresent()) {
            return new ResponseEntity<>(team.get(), HttpStatus.OK);
        } else {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }

    @PostMapping
    public ResponseEntity<Team> addTeam(@RequestBody Team team) {
        Team savedTeam = teamRepository.save(team);
        return new ResponseEntity<>(savedTeam, HttpStatus.CREATED);
    }

    @PutMapping("/{id}")
    public ResponseEntity<Team> updateTeam(@PathVariable Long id, @RequestBody Team teamDetails) {
        Optional<Team> teamData = teamRepository.findById(id);

        if (teamData.isPresent()) {
            Team existingTeam = teamData.get();
            existingTeam.setTeamName(teamDetails.getTeamName());

            Team updatedTeam = teamRepository.save(existingTeam);
            return new ResponseEntity<>(updatedTeam, HttpStatus.OK);
        } else {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteTeam(@PathVariable Long id) {
        if (teamRepository.existsById(id)) {
            teamRepository.deleteById(id);
            return new ResponseEntity<>(HttpStatus.NO_CONTENT);
        } else {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }
}