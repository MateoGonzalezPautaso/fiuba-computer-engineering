import subprocess
import pytest

@pytest.mark.describe('ADPCM')
class TestADPCM():
    @pytest.mark.it('2048 2 way 64 sets summary')
    def test_adpcm_2048_2_64_summary(self):
        args = ['./cachesim','./trazas/adpcm.xex','2048','2','64']

        result = subprocess.run(args, capture_output=True, text=True)
        exit_code = result.returncode

        assert exit_code == 0

        stdout = result.stdout.splitlines()
        data = ''
        with open('./output/adpcm_2048-2-64_summary.txt','r') as f:
            data = f.read().splitlines()
        
        for line_data, line_stdout in zip(data,stdout):
            assert line_data == line_stdout

    @pytest.mark.it('2048 2 way 64 sets')
    def test_adpcm_2048_2_64(self):
        args = ['./cachesim','./trazas/adpcm.xex','2048','2','64','-v','0','15000']

        result = subprocess.run(args, capture_output=True, text=True)
        exit_code = result.returncode

        assert exit_code == 0

        stdout = result.stdout.splitlines()
        data = ''
        with open('./output/adpcm_2048-2-64.txt','r') as f:
            data = f.read().splitlines()
        
        for line_data, line_stdout in zip(data,stdout):
            assert line_data == line_stdout

    @pytest.mark.it('4096 direct-mapped')
    def test_adpcm_4096(self):
        args = ['./cachesim','./trazas/adpcm.xex','4096','1','256','-v','0','10000']

        result = subprocess.run(args, capture_output=True, text=True)
        exit_code = result.returncode

        assert exit_code == 0

        stdout = result.stdout.splitlines()
        data = ''
        with open('./output/adpcm_4096-1-256.txt','r') as f:
            data = f.read().splitlines()
        
        for line_data, line_stdout in zip(data,stdout):
            assert line_data == line_stdout