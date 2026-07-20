package is1;

import org.testng.annotations.Test;
import static org.testng.Assert.assertEquals;

public class GameTest {

    private Move rock = new Rock();
    private Move paper = new Paper();
    private  Move scissors = new Scissors();

    @Test
    public void testGameRockAgainstPaper() {
        Player computerPlayer = () -> rock;
        Player humanPlayer = () -> paper;
        Move result = computerPlayer.getMove().vs(humanPlayer.getMove());
        assertEquals(result, humanPlayer.getMove());
    }

    @Test
    public void testGameRockAgainstScissors() {
        Player computerPlayer = () -> rock;
        Player humanPlayer = () -> scissors;
        Move result = computerPlayer.getMove().vs(humanPlayer.getMove());
        assertEquals(result, computerPlayer.getMove());
    }

    @Test
    public void testGamePaperAgainstScissors() {
        Player computerPlayer = () -> paper;
        Player humanPlayer = () -> scissors;
        Move result = computerPlayer.getMove().vs(humanPlayer.getMove());
        assertEquals(result, humanPlayer.getMove());
    }

}
