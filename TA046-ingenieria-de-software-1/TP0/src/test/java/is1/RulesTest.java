package is1;

import org.testng.annotations.Test;
import static org.testng.Assert.assertEquals;

public class RulesTest {

    private Move rock = new Rock();
    private Move paper = new Paper();
    private  Move scissors = new Scissors();

    // Rock vs everything
    @Test
    public void rockBeatsScissors() {
        assertEquals(rock, rock.vs(scissors));
    }

    @Test
    public void rockLosesWithPaper() {
        assertEquals(paper, rock.vs(paper));
    }

    @Test
    public void rockBeatsRock() {
        assertEquals(rock, rock.vs(rock));
    }

    // Paper vs everything
    @Test
    public void paperBeatsRock() {
        assertEquals(paper, paper.vs(rock));
    }

    @Test
    public void paperLosesWithScissors() {
        assertEquals(scissors, paper.vs(scissors));
    }

    @Test
    public void paperBeatsPaper() {
        assertEquals(paper, paper.vs(paper));
    }

    // Scissors vs everything
    @Test
    public void scissorsBeatsPaper() { assertEquals(scissors, scissors.vs(paper)); }

    @Test
    public void scissorsLosesWithRock() {
        assertEquals(rock, scissors.vs(rock));
    }

    @Test
    public void scissorsBeatsScissors() {
        assertEquals(scissors, scissors.vs(scissors));
    }

}
