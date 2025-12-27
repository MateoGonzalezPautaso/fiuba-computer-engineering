import subprocess
import pytest

@pytest.mark.it('Verifica que C es potencia de 2')
def test_C():
    args = ['./cachesim','empty.xex','2047','2','64']

    result = subprocess.run(args, capture_output=True, text=True)
    exit_code = result.returncode
    stderr = result.stderr.strip()

    assert exit_code != 0
    assert stderr != ''

@pytest.mark.it('Verifica que E es potencia de 2')
def test_E():
    args = ['./cachesim','empty.xex','2048','9','64']

    result = subprocess.run(args, capture_output=True, text=True)
    exit_code = result.returncode
    stderr = result.stderr.strip()

    assert exit_code != 0
    assert stderr != ''

@pytest.mark.it('Verifica que S es potencia de 2')
def test_S():
    args = ['./cachesim','empty.xex','2048','2','60']

    result = subprocess.run(args, capture_output=True, text=True)
    exit_code = result.returncode
    stderr = result.stderr.strip()

    assert exit_code != 0
    assert stderr != ''

@pytest.mark.it('No permite rangos inválidos (n ≥ m)')
def test_invalid_n_m():
    args = ['./cachesim','empty.xex','2048','2','64','-v','200','150']

    result = subprocess.run(args, capture_output=True, text=True)
    exit_code = result.returncode
    stderr = result.stderr.strip()

    assert exit_code != 0
    assert stderr != ''

@pytest.mark.it('Emite error en stderr para combinación inválida de C/E/S')
def test_invalid_CES():
    args = ['./cachesim','empty.xex','2048','32','256']

    result = subprocess.run(args, capture_output=True, text=True)
    exit_code = result.returncode
    stderr = result.stderr.strip()

    assert exit_code != 0
    assert stderr != ''


