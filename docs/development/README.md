# Development research

- [K/M diagnostic signals and contribution boundaries](eurocontrol-lpb-diagnostics.md):
  scoped request/lock/status fields, burner/DHW configuration, evidence levels,
  open questions, and the relationship to the external dashboard.
- [Controlled M operating-mode test](eurocontrol-mode-test-20261110.json):
  selected checksum-verifiable read frames for continuous, standby and Auto return.
- [Read-only object index](eurocontrol-readonly-object-index.json):
  133 collector fields on 123 controller/object combinations; not automatic
  firmware definitions or authorization to write those objects.

- [Eurocontrol K legacy LPB observations](eurocontrol-k-lpb.md): confirmed object
  mappings, optional-value behavior, pump block layout, and review boundaries.
- [Eurocontrol M legacy LPB read profile](eurocontrol-m-lpb.md): read-only mixing
  controller values, pump/mixer contact layout, and physical validation limits.
- [Inspecting locally supplied Siemens system definitions](siemens-sysdef-research.md):
  offline package structure, reader usage, parser coverage, and known limits.
- [Compact verified facts](rva43-verified-facts.json): machine-readable evidence
  for targeted family-specific work; not a replacement for the full vendor data.
- [Eurocontrol M facts](rva46-verified-facts.json): successful read samples,
  source offsets, and the observed pump-on/mixer-off comparison.

The development branch is based on the upstream project, with independent code
fixes kept separate from research tooling and findings. Vendor archives and
private device configuration are not part of this repository.
