import subprocess
import pytest

@pytest.mark.describe('Blowfish')
class TestBlowfish():
    @pytest.mark.it('4096 4 way 16 sets summary')
    def test_blowfish_4096_4_16_summary(self):
        args = ['./cachesim','./trazas/blowfish.xex','4096','4','16']

        result = subprocess.run(args, capture_output=True, text=True)
        exit_code = result.returncode

        assert exit_code == 0

        stdout = result.stdout.splitlines()
        data = ''
        with open('./output/blowfish_4096-4-16_summary.txt','r') as f:
            data = f.read().splitlines()
        
        for line_data, line_stdout in zip(data,stdout):
            assert line_data == line_stdout

    @pytest.mark.it('4096 direct-mapped')
    def test_blowfish_4096_1_256(self):
        args = ['./cachesim','./trazas/blowfish.xex','4096','1','256','-v','0','10000']

        result = subprocess.run(args, capture_output=True, text=True)
        exit_code = result.returncode

        assert exit_code == 0

        stdout = result.stdout.splitlines()
        data = ''
        with open('./output/blowfish_4096-1-256.txt','r') as f:
            data = f.read().splitlines()
        
        for line_data, line_stdout in zip(data,stdout):
            assert line_data == line_stdout

    @pytest.mark.it('1024 2 way 32 sets')
    def test_blowfish_4096_4_16(self):
        args = ['./cachesim','./trazas/blowfish.xex','1024','2','32','-v','0','15000']

        result = subprocess.run(args, capture_output=True, text=True)
        exit_code = result.returncode

        assert exit_code == 0

        stdout = result.stdout.splitlines()
        data = ''
        with open('./output/blowfish_1024-2-32.txt','r') as f:
            data = f.read().splitlines()
        
        for line_data, line_stdout in zip(data,stdout):
            assert line_data == line_stdout